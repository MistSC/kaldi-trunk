// nnet/nnet-tcn.h

#ifndef KALDI_NNET_NNET_TCN_H_
#define KALDI_NNET_NNET_TCN_H_

#include <iostream>
#include <vector>
#include "nnet/nnet-component.h"
#include "nnet/nnet-various.h"
#include "cudamatrix/cu-math.h"

namespace kaldi {
namespace nnet1 {
class TCNComponent : public UpdatableComponent {
 public:
 TCNComponent(int32 dim_in,int32 dim_out)
    : UpdatableComponent(dim_in, dim_out),
      //initial dimension parameters
      dim_in_(dim_in),dim_out_(dim_out),
      wei_1_i1_(0.0),wei_2_i2_(0.0),wei_1_j1_(0.0),wei_2_j2_(0.0),
      input_dim_1_(0.0),input_dim_2_(0.0),
      output_dim_1_(0.0),output_dim_2_(0.0),
      //initial learning rate
      learn_rate_coef_(1.0), bias_learn_rate_coef_(1.0)
  { }
  ~TCNComponent()
  { }

  

  Component* Copy() const { return new TCNComponent(*this); }
  ComponentType GetType() const { return scTCNComponent; }

  void InitData(std::istream &is) {
    // define options
    BaseFloat bias_mean = -2.0, bias_range = 2.0, param_stddev = 0.1;//stddev标准差
    BaseFloat learn_rate_coef = 1.0, bias_learn_rate_coef = 1.0;
    // parse config
    std::string token;
    while (!is.eof()) {
      ReadToken(is, false, &token);
      /**//*if  (token == "<InputDim>")      ReadBasicType(is, false, &input_dim_);
      else if (token == "<OutputDim>")     ReadBasicType(is, false, &output_dim_);*/
      if (token == "<BiasMean>")      ReadBasicType(is, false, &bias_mean);
      else if (token == "<BiasRange>")     ReadBasicType(is, false, &bias_range);
      else if (token == "<ParamStddev>")   ReadBasicType(is, false, &param_stddev);
      else if (token == "<InputDim1>")       ReadBasicType(is, false, &input_dim_1_);
      else if (token == "<InputDim2>")       ReadBasicType(is, false, &input_dim_2_);
      else if (token == "<OutputDim1>")      ReadBasicType(is, false, &output_dim_1_);
      else if (token == "<OutputDim2>")      ReadBasicType(is, false, &output_dim_2_);
      //else if (token == "<LearnRateCoef>") ReadBasicType(is, false, &learn_rate_coef);
      //else if (token == "<BiasLearnRateCoef>") ReadBasicType(is, false, &bias_learn_rate_coef);
      else KALDI_ERR << "Unknown token " << token << ", a typo in config?"
                     << " (ParamStddev|BiasMean|BiasRange|FmapXLen|FmapYLen|FiltXLen|FiltYLen|FiltXStep|FiltYStep|ConnectFmap|LearnRateCoef|BiasLearnRateCoef)";
      is >> std::ws;  // eat-up whitespace
    }
  
    /*
    KALDI_LOG<< "===================tokening is over==================";
    KALDI_LOG<< "dim_in_: " << dim_in_;
    KALDI_LOG<< "dim_out_: " << dim_out_;
    //KALDI_LOG<< "input_dim_: " << input_dim_;
    //KALDI_LOG<< "output_dim_: " << output_dim_;
    KALDI_LOG<< "input dimension for way 1: " << input_dim_1_;
    KALDI_LOG<< "input dimension for way 2: " << input_dim_2_;
    KALDI_LOG<< "output dimension for way 2: " << output_dim_1_;
    KALDI_LOG<< "output dimension for way 2: " << output_dim_2_;
    KALDI_LOG<< "BiasMean:" << bias_mean;
    KALDI_LOG<< "BiasRange: " << bias_range;
    KALDI_LOG<< "ParamStddev: " << param_stddev;
    */

    //===============================================================//
    //                      Sanity checks:                           //
    //===============================================================//
    // input sanity checks
    KALDI_ASSERT(dim_in_ == input_dim_1_ * input_dim_2_);
        
    // output sanity checks
    KALDI_ASSERT(dim_out_ == output_dim_1_ * output_dim_2_);

    //===============================================================//
    //                Initialize parameters                          //
    //===============================================================//
    
    //initial dimension parameters
    wei_1_i1_ = input_dim_1_; 
    wei_1_j1_ = output_dim_1_;
    wei_2_i2_ = input_dim_2_;
    wei_2_j2_ = output_dim_2_;

    //initialize weights
    Matrix<BaseFloat> mat_w1(wei_1_j1_,wei_1_i1_);
    Matrix<BaseFloat> mat_w2(wei_2_j2_,wei_2_i2_);
    for (int32 r = 0; r < wei_1_j1_; r++) {
      for (int32 c = 0; c < wei_1_i1_; c++) {
        // 0-mean Gauss with given std_dev for weight 1
        mat_w1(r, c) = param_stddev * RandGauss();
      }
    }
    for (int32 r = 0; r < wei_2_j2_; r++) {
      for (int32 c = 0; c < wei_2_i2_; c++) {
        // 0-mean Gauss with given std_dev for weight 2
        mat_w2(r, c) = param_stddev * RandGauss();
      }
    }
    mode_1_wei_ = mat_w1;     //mode 1 product weight
    mode_2_wei_ = mat_w2;     //mode 2 product weight

    //initialize bias
    Matrix<BaseFloat> mat_b(wei_1_j1_,wei_2_j2_);
    for (int32 r = 0; r < wei_1_j1_; r++) {
      for (int32 c = 0; c< wei_2_j2_; c++) {
        // +/- 1/2*bias_range      from bias_mean:
        mat_b(r,c) = bias_mean + (RandUniform() - 0.5) * bias_range;
      }
    }
    bias_ = mat_b;

    learn_rate_coef_ = learn_rate_coef;
    bias_learn_rate_coef_ = bias_learn_rate_coef;
    // initial gradients
    mode_1_wei_grad_.Resize(wei_1_j1_, wei_1_i1_);
    mode_2_wei_grad_.Resize(wei_2_j2_, wei_2_i2_);
    bias_grad_.Resize(wei_1_j1_, wei_2_j2_);
  }

  void ReadData(std::istream &is, bool binary) {
    ExpectToken(is, binary, "<LearnRateCoef>");
    ReadBasicType(is, binary, &learn_rate_coef_);
    ExpectToken(is, binary, "<BiasLearnRateCoef>");
    ReadBasicType(is, binary, &bias_learn_rate_coef_);

    // input output dimension parameters
    ExpectToken(is, binary, "<InputDim1>");
    ReadBasicType(is, binary, &input_dim_1_);
    ExpectToken(is, binary, "<InputDim2>");
    ReadBasicType(is, binary, &input_dim_2_);
    ExpectToken(is, binary, "<OutputDim1>");
    ReadBasicType(is, binary, &output_dim_1_);
    ExpectToken(is, binary, "<OutputDim2>");
    ReadBasicType(is, binary, &output_dim_2_);
    
    // weight dimension parameters
    ExpectToken(is, binary, "<Wei1Col>");
    ReadBasicType(is, binary, &wei_1_i1_);
    ExpectToken(is, binary, "<Wei1Row>");
    ReadBasicType(is, binary, &wei_1_j1_);
    ExpectToken(is, binary, "<Wei2Col>");
    ReadBasicType(is, binary, &wei_2_i2_);
    ExpectToken(is, binary, "<Wei2Row>");
    ReadBasicType(is, binary, &wei_2_j2_);

    // trainable parameters
    ExpectToken(is, binary, "<Mode1Weight>");
    mode_1_wei_.Read(is, binary);
    ExpectToken(is, binary, "<Mode2Weight>");
    mode_2_wei_.Read(is, binary);
    ExpectToken(is, binary, "<Bias>");
    bias_.Read(is, binary);

    // initial gradients
    mode_1_wei_grad_.Resize(wei_1_j1_, wei_1_i1_);
    mode_2_wei_grad_.Resize(wei_2_j2_, wei_2_i2_);
    bias_grad_.Resize(wei_1_j1_, wei_2_j2_);

  }

  void WriteData(std::ostream &os, bool binary) const {
    WriteToken(os, binary, "<LearnRateCoef>");
    WriteBasicType(os, binary, learn_rate_coef_);
    WriteToken(os, binary, "<BiasLearnRateCoef>");
    WriteBasicType(os, binary, bias_learn_rate_coef_);

    // input output dimension parameters
    WriteToken(os, binary, "<InputDim1>");
    WriteBasicType(os, binary, input_dim_1_);
    WriteToken(os, binary, "<InputDim2>");
    WriteBasicType(os, binary, input_dim_2_);
    WriteToken(os, binary, "<OutputDim1>");
    WriteBasicType(os, binary, output_dim_1_);
    WriteToken(os, binary, "<OutputDim2>");
    WriteBasicType(os, binary, output_dim_2_);

    // weight dimension parameters
    WriteToken(os, binary, "<Wei1Col>");
    WriteBasicType(os, binary, wei_1_i1_);
    WriteToken(os, binary, "<Wei1Row>");
    WriteBasicType(os, binary, wei_1_j1_);
    WriteToken(os, binary, "<Wei2Col>");
    WriteBasicType(os, binary, wei_2_i2_);
    WriteToken(os, binary, "<Wei2Row>");
    WriteBasicType(os, binary, wei_2_j2_);

    // trainable parameters
    WriteToken(os, binary, "<Mode1Weight>");
    mode_1_wei_.Write(os, binary);
    WriteToken(os, binary, "<Mode2Weight>");
    mode_2_wei_.Write(os, binary);
    WriteToken(os, binary, "<Bias>");
    bias_.Write(os, binary);
    
  }

  int32 NumParams() const {
    return mode_1_wei_.NumRows() * mode_1_wei_.NumCols()\
           +mode_2_wei_.NumRows() * mode_2_wei_.NumCols()\
           +bias_.NumRows() * bias_.NumCols(); 
  }

  void GetParams(Vector<BaseFloat>* wei_copy) const {
    //make a stack memories for all weights
    wei_copy->Resize(NumParams());
    int32 weight_1_num_elem = mode_1_wei_.NumRows() * mode_1_wei_.NumCols();
    int32 weight_2_num_elem = mode_2_wei_.NumRows() * mode_2_wei_.NumCols();
    int32 bias_num_elem = bias_.NumRows() * bias_.NumCols();
    //Range(o,l) o:original l:length
    wei_copy->Range(0, weight_1_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(mode_1_wei_));
    wei_copy->Range(weight_1_num_elem, weight_2_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(mode_2_wei_));
    wei_copy->Range(weight_1_num_elem+weight_2_num_elem, bias_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(bias_));
  }

  std::string Info() const {
    //Optionally print some additional info
    return std::string("\n  mode_1_weights") + MomentStatistics(mode_1_wei_) +
           "\n  mode_2_weights" +  MomentStatistics(mode_2_wei_) +
           "\n  bias" + MomentStatistics(bias_);
  }
  std::string InfoGradient() const {
    //Reimplemented from Component
    return std::string("\n  mode_1_grad") + MomentStatistics(mode_1_wei_grad_) +
           "\n  mode_2_grad" + MomentStatistics(mode_2_wei_grad_) +            
           ", lr-coef " + ToString(learn_rate_coef_) +
           "\n  bias_grad" + MomentStatistics(bias_grad_) +
           ", lr-coef " + ToString(bias_learn_rate_coef_);
  }

void TuckerFeedForward(const CuMatrixBase<BaseFloat> &wei1, const CuMatrixBase<BaseFloat> &wei2,
                         const CuMatrixBase<BaseFloat> &in, CuMatrixBase<BaseFloat>* out)
  {
    //KALDI_LOG<<"wei1:"<<"("<<wei1.NumRows()<<","<<wei1.NumCols()<<")";
    //KALDI_LOG<<"wei2:"<<"("<<wei2.NumRows()<<","<<wei2.NumCols()<<")";
    //KALDI_LOG<<"in:("<<in.NumRows()<<","<<in.NumCols()<<")";
    //KALDI_LOG<<"out"<<"("<<out->NumRows()<<","<<out->NumCols()<<")";

    int32 ib = out->NumRows();
    int32 j1 = wei1.NumRows(), i1 = wei1.NumCols();
    int32 j2 = wei2.NumRows(), i2 = wei2.NumCols();
    // give initial size
    CuMatrix<BaseFloat> output(ib, j1 * j2);
    CuMatrix<BaseFloat> temp(ib, j1 * i2);
    // reshape to std::vector
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_input;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_output;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_temp;
    // w1_vec and w2_vec used to parallel
    std::vector< CuSubMatrix<BaseFloat>* > w1_vec;
    std::vector< CuSubMatrix<BaseFloat>* > w2_vec;
    CuSubMatrix<BaseFloat>* w1 = new CuSubMatrix<BaseFloat>(wei1,0,j1,0,i1);
    CuSubMatrix<BaseFloat>* w2 = new CuSubMatrix<BaseFloat>(wei2,0,j2,0,i2);
    // initial some vectors
    for(int32 i = 0; i < ib; i++)
    {
      CuSubMatrix<BaseFloat> *temp_reshaped_input = new CuSubMatrix<BaseFloat>(in,i,i1,i2);
      CuSubMatrix<BaseFloat> *temp_reshaped_temp = new CuSubMatrix<BaseFloat>(temp,i,j1,i2);
      CuSubMatrix<BaseFloat> *temp_reshaped_output = new CuSubMatrix<BaseFloat>(output,i,j1,j2);
      w1_vec.push_back(w1);
      w2_vec.push_back(w2);
      reshaped_input.push_back(temp_reshaped_input);
      reshaped_temp.push_back(temp_reshaped_temp);
      reshaped_output.push_back(temp_reshaped_output);
    }
    AddMatMatBatched<BaseFloat>(1.0,reshaped_temp,w1_vec,kNoTrans,reshaped_input,kNoTrans,0.0);
    AddMatMatBatched<BaseFloat>(1.0,reshaped_output,reshaped_temp,kNoTrans,w2_vec,kTrans,0.0);
    out->CopyFromMat(output);
    // delete pointers
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_input.begin(); i!=reshaped_input.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_output.begin(); i!=reshaped_output.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_temp.begin(); i!=reshaped_temp.end(); ++i)
      delete *i;
    delete w1; delete w2;
  }
  
  // note: out_diff should be tensor type 1, this can save some memory and computation
  void TuckerBackProp(const CuMatrixBase<BaseFloat> &wei1, const CuMatrixBase<BaseFloat> &wei2,
                      const CuMatrixBase<BaseFloat> &out_diff, CuMatrixBase<BaseFloat> *in_diff)
  {
    int32 ib = out_diff.NumRows();
    int32 j1 = wei1.NumRows(), i1 = wei1.NumCols();
    int32 j2 = wei2.NumRows(), i2 = wei2.NumCols();
    // given initial size
    CuMatrix<BaseFloat> temp(ib, i1 * j2);
    CuMatrix<BaseFloat> input_diff(ib, i1 * i2);
    // reshape to std::vector
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_temp;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_input_diff;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_output_diff;
    // w1_vec and w2_vec used to parallel
    std::vector< CuSubMatrix<BaseFloat>* > w1_vec;
    std::vector< CuSubMatrix<BaseFloat>* > w2_vec;
    CuSubMatrix<BaseFloat>* w1 = new CuSubMatrix<BaseFloat>(wei1,0,j1,0,i1);
    CuSubMatrix<BaseFloat>* w2 = new CuSubMatrix<BaseFloat>(wei2,0,j2,0,i2);
    // initial some vectors
    for(int32 i = 0; i < ib; i++)
    {
      CuSubMatrix<BaseFloat> *temp_reshaped_temp = new CuSubMatrix<BaseFloat>(temp,i,i1,j2);               //i1 * j2
      CuSubMatrix<BaseFloat> *temp_reshaped_output_diff = new CuSubMatrix<BaseFloat>(out_diff,i,j1,j2);    //j1 * j2
      CuSubMatrix<BaseFloat> *temp_reshaped_input_diff = new CuSubMatrix<BaseFloat>(input_diff,i,i1,i2);   //i1 * i2
      w1_vec.push_back(w1);
      w2_vec.push_back(w2);
      reshaped_temp.push_back(temp_reshaped_temp);
      reshaped_output_diff.push_back(temp_reshaped_output_diff);
      reshaped_input_diff.push_back(temp_reshaped_input_diff);
    }
    AddMatMatBatched<BaseFloat>(1.0,reshaped_temp,w1_vec,kTrans,reshaped_output_diff,kNoTrans,0.0);
    AddMatMatBatched<BaseFloat>(1.0,reshaped_input_diff,reshaped_temp,kNoTrans,w2_vec,kNoTrans,0.0);
    
    in_diff->CopyFromMat(input_diff);
    // delete pointers
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_temp.begin(); i!=reshaped_temp.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_input_diff.begin(); i!=reshaped_input_diff.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_output_diff.begin(); i!=reshaped_output_diff.end(); ++i)
      delete *i;
    delete w1; delete w2;
  }

    // note: in and diff should be tensor type 0, it's easy to compute
  void TuckerCalcGrad(const CuMatrixBase<BaseFloat> &wei1, const CuMatrixBase<BaseFloat> &wei2,
                      const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &diff,
                      CuMatrixBase<BaseFloat> *gw1, CuMatrixBase<BaseFloat> *gw2, CuMatrixBase<BaseFloat> *gb, 
                      const BaseFloat mmt)
  {
    //KALDI_LOG<<"wei1:("<<wei1.NumRows()<<","<<wei1.NumCols()<<")";
    //KALDI_LOG<<"wei2:("<<wei2.NumRows()<<","<<wei2.NumCols()<<")";
    //KALDI_LOG<<"in:("<<in.NumRows()<<","<<in.NumCols()<<")";
    //KALDI_LOG<<"diff:("<<diff.NumRows()<<","<<diff.NumCols()<<")";
    //KALDI_LOG<<"gw1:("<<gw1->NumRows()<<","<<gw1->NumCols()<<")";
    //KALDI_LOG<<"gw2:("<<gw2->NumRows()<<","<<gw2->NumCols()<<")";
    //KALDI_LOG<<"gb:("<<gb->NumRows()<<","<<gb->NumCols()<<")";

    int32 ib = in.NumRows();
    int32 j1 = wei1.NumRows(), i1 = wei1.NumCols();
    int32 j2 = wei2.NumRows(), i2 = wei2.NumCols();
    // give initial size
    //gw1->Resize(j1, i1);
    //gw2->Resize(j2, i2);
    CuMatrix<BaseFloat> input(ib, j1 * i2);
    CuMatrix<BaseFloat> dif(ib, j1 * j2);
    CuMatrix<BaseFloat> temp_w1(ib, j1 * i2);
    CuMatrix<BaseFloat> temp_w2(ib, j2 * i1);
    CuMatrix<BaseFloat> w1_grad_batch(ib, j1 * i1);
    CuMatrix<BaseFloat> w2_grad_batch(ib, j2 * i2);
    // reshape to std::vector
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_input;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_diff;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_temp_w1;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_temp_w2;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_w1_grad_batch;
    std::vector< CuSubMatrix<BaseFloat>* > reshaped_w2_grad_batch;
    // w1_vec and w2_vec used to parallel
    std::vector< CuSubMatrix<BaseFloat>* > w1_vec;
    std::vector< CuSubMatrix<BaseFloat>* > w2_vec;
    CuSubMatrix<BaseFloat>* w1 = new CuSubMatrix<BaseFloat>(wei1,0,j1,0,i1);
    CuSubMatrix<BaseFloat>* w2 = new CuSubMatrix<BaseFloat>(wei2,0,j2,0,i2);
    // initial some vectors
    for(int32 i = 0; i < ib; i++)
    {
      CuSubMatrix<BaseFloat> *temp_reshaped_input = new CuSubMatrix<BaseFloat>(in,i,i1,i2);
      CuSubMatrix<BaseFloat> *temp_reshaped_diff = new CuSubMatrix<BaseFloat>(diff,i,j1,j2);
      CuSubMatrix<BaseFloat> *temp_reshaped_temp_w1 = new CuSubMatrix<BaseFloat>(temp_w1,i,j1,i2);                  //j1 * i2
      CuSubMatrix<BaseFloat> *temp_reshaped_temp_w2 = new CuSubMatrix<BaseFloat>(temp_w2,i,j2,i1);                  //j2 * i1
      CuSubMatrix<BaseFloat> *temp_w1_grad_batch = new CuSubMatrix<BaseFloat>(w1_grad_batch,i,j1,i1);               //j1 * i1
      CuSubMatrix<BaseFloat> *temp_w2_grad_batch = new CuSubMatrix<BaseFloat>(w2_grad_batch,i,j2,i2);               //j2 * i2
      w1_vec.push_back(w1);
      w2_vec.push_back(w2);
      reshaped_input.push_back(temp_reshaped_input);
      reshaped_diff.push_back(temp_reshaped_diff);
      reshaped_temp_w1.push_back(temp_reshaped_temp_w1);
      reshaped_temp_w2.push_back(temp_reshaped_temp_w2);
      reshaped_w1_grad_batch.push_back(temp_w1_grad_batch);
      reshaped_w2_grad_batch.push_back(temp_w2_grad_batch);
    }
    // compute gradient
    // we have w1 and w2 gradient
    // compute w1 grad
    AddMatMatBatched<BaseFloat>(1.0,reshaped_temp_w1,reshaped_diff,kNoTrans,w2_vec,kNoTrans,0.0);
    AddMatMatBatched<BaseFloat>(1.0,reshaped_w1_grad_batch,reshaped_temp_w1,kNoTrans,reshaped_input,kTrans,0.0);
    CuVector<BaseFloat> w1_grad_vec_temp(j1 * i1);
    w1_grad_vec_temp.AddRowSumMat(1.0,w1_grad_batch);
    gw1->CopyRowsFromVec(w1_grad_vec_temp);
    gw1->AddMat(mmt,*gw1);
    // compute w2 grad
    AddMatMatBatched<BaseFloat>(1.0,reshaped_temp_w2,reshaped_diff,kTrans,w1_vec,kNoTrans,0.0);
    AddMatMatBatched<BaseFloat>(1.0,reshaped_w2_grad_batch,reshaped_temp_w2,kNoTrans,reshaped_input,kNoTrans,0.0);
    CuVector<BaseFloat> w2_grad_vec_temp(j2 * i2);
    w2_grad_vec_temp.AddRowSumMat(1.0,w2_grad_batch);
    gw2->CopyRowsFromVec(w2_grad_vec_temp);
    gw2->AddMat(mmt,*gw2);
    // bias
    CuVector<BaseFloat> bias_grad_vec_temp(j1 * j2);
    bias_grad_vec_temp.AddRowSumMat(1.0,diff);
    gb->CopyRowsFromVec(bias_grad_vec_temp);
    gb->AddMat(mmt,*gb);
    // delete pointers
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_input.begin(); i!=reshaped_input.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_diff.begin(); i!=reshaped_diff.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_temp_w1.begin(); i!=reshaped_temp_w1.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_temp_w2.begin(); i!=reshaped_temp_w2.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_w1_grad_batch.begin(); i!=reshaped_w1_grad_batch.end(); ++i)
      delete *i;
    for(std::vector< CuSubMatrix<BaseFloat>* >::iterator i=reshaped_w2_grad_batch.begin(); i!=reshaped_w2_grad_batch.end(); ++i)
      delete *i;
    delete w1; delete w2;
  }

  
  
  //if n=1  X:i1*i2 w:j1*i1 out:j1*i2
  //out = w * X
  //if n=2  X:i1*i2 w:j2*i2 out:i1*j2
  //out = X * w^T
  //X *1 w1 *2 w2 = w1 * X * w2^T
  void PropagateFnc(const CuMatrixBase<BaseFloat> &in, CuMatrixBase<BaseFloat> *out) 
  { 
     //KALDI_LOG<<"FeedForward";
     TuckerFeedForward(mode_1_wei_, mode_2_wei_,
                       in, out);
  }


  void BackpropagateFnc(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &out,
                        const CuMatrixBase<BaseFloat> &out_diff, CuMatrixBase<BaseFloat> *in_diff)                       
  {
    //KALDI_LOG<<"BackpropagateFnc";
    TuckerBackProp(mode_1_wei_, mode_2_wei_,
                   out_diff, in_diff);
    
    const BaseFloat mmt = opts_.momentum;
    TuckerCalcGrad(mode_1_wei_, mode_2_wei_,
                   in, out_diff,
                   &mode_1_wei_grad_,&mode_2_wei_grad_, &bias_grad_, 
                   mmt);
  }

  //update back propagation
  void Update(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &diff) 
  {
   // KALDI_LOG<<"Update";
    // we use following hyperparameters from the option class
    const BaseFloat lr = opts_.learn_rate * learn_rate_coef_;
    const BaseFloat lr_bias = opts_.learn_rate * bias_learn_rate_coef_;
    //const BaseFloat mmt = opts_.momentum;
    const BaseFloat l2 = opts_.l2_penalty;
    const BaseFloat l1 = opts_.l1_penalty;

    // we will also need the number of frames in the mini-batch
    const int32 batch_size = in.NumRows();
    // l2 regularization
    if (l2 != 0.0)
    {
      mode_1_wei_grad_.AddMat(-lr*l2*batch_size,mode_1_wei_grad_);
      mode_2_wei_grad_.AddMat(-lr*l2*batch_size,mode_2_wei_grad_);
    }
    // l1 regularization
    if (l1 != 0.0)
    {
      cu::RegularizeL1(&mode_1_wei_, &mode_1_wei_grad_, lr*l1*batch_size, lr);
      cu::RegularizeL1(&mode_2_wei_, &mode_2_wei_grad_, lr*l1*batch_size, lr);
    }
    // update
    mode_1_wei_.AddMat(-lr, mode_1_wei_grad_);
    mode_2_wei_.AddMat(-lr,mode_2_wei_grad_);
    bias_.AddMat(-lr_bias,bias_grad_);
  }

  const CuMatrixBase<BaseFloat>& GetCuMatrixBase(CuMatrix<BaseFloat>& cumatrix)
  {
    return cumatrix;
  }


 private:
  int32 wei_1_i1_,wei_1_j1_,       //weight 1 dimensions for input data row
        wei_2_i2_,wei_2_j2_;       //weight 2 dimensions for input data column

  int32 input_dim_1_,input_dim_2_;   //input matrix dimension
  int32 output_dim_1_,output_dim_2_; //output matrix dimension
  int32 dim_in_,dim_out_;      //these two parameter is used for checking

  BaseFloat learn_rate_coef_;
  BaseFloat bias_learn_rate_coef_;

  //weight of mode 1 2 product and bias
  CuMatrix<BaseFloat> mode_1_wei_;           //j1*i1
  CuMatrix<BaseFloat> mode_2_wei_;           //j2*i2
  CuMatrix<BaseFloat> bias_;                 //j1*j2

  //gradient of mode 1 2 product and bias
  CuMatrix<BaseFloat>  mode_1_wei_grad_;
  CuMatrix<BaseFloat>  mode_2_wei_grad_;
  CuMatrix<BaseFloat>  bias_grad_;

};

}  // namespace nnet1
}  // namespace kaldi

#endif
