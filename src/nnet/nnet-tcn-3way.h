// nnet/nnet-tcn.h

#ifndef KALDI_NNET_NNET_TCN_3WAY_H_
#define KALDI_NNET_NNET_TCN_3WAY_H_

#include <iostream>
#include <vector>
#include "nnet/nnet-component.h"
#include "nnet/nnet-various.h"
#include "cudamatrix/cu-math.h"

namespace kaldi {
namespace nnet1 {
class TCN3WayComponent : public UpdatableComponent {
 public:
 TCN3WayComponent(int32 dim_in,int32 dim_out)
    : UpdatableComponent(dim_in, dim_out),
      //initial dimension parameters
      dim_in_(dim_in),dim_out_(dim_out),
      wei_1_i1_(0.0),wei_2_i2_(0.0),wei_3_i3_(0.0),
      wei_1_j1_(0.0),wei_2_j2_(0.0),wei_3_j3_(0.0),
      input_dim_1_(0.0),input_dim_2_(0.0),input_dim_3_(0.0),
      output_dim_1_(0.0),output_dim_2_(0.0),output_dim_3_(0.0),
      //initial learning rate
      learn_rate_coef_(1.0), bias_learn_rate_coef_(1.0)
  { }
  ~TCN3WayComponent()
  { }

  

  Component* Copy() const { return new TCN3WayComponent(*this); }
  ComponentType GetType() const { return scTCN3WayComponent; }

  void InitData(std::istream &is) {
    // define options
    BaseFloat bias_mean = -2.0, bias_range = 2.0, param_stddev = 0.1;//stddev标准差
    BaseFloat learn_rate_coef = 1.0, bias_learn_rate_coef = 1.0;
    // parse config
    std::string token;
    while (!is.eof()) {
      ReadToken(is, false, &token);
      if (token == "<BiasMean>")      ReadBasicType(is, false, &bias_mean);
      else if (token == "<BiasRange>")     ReadBasicType(is, false, &bias_range);
      else if (token == "<ParamStddev>")   ReadBasicType(is, false, &param_stddev);
      else if (token == "<InputDim1>")       ReadBasicType(is, false, &input_dim_1_);
      else if (token == "<InputDim2>")       ReadBasicType(is, false, &input_dim_2_);
      else if (token == "<InputDim3>")       ReadBasicType(is, false, &input_dim_3_);
      else if (token == "<OutputDim1>")      ReadBasicType(is, false, &output_dim_1_);
      else if (token == "<OutputDim2>")      ReadBasicType(is, false, &output_dim_2_);
      else if (token == "<OutputDim3>")      ReadBasicType(is, false, &output_dim_3_);
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
    KALDI_ASSERT(dim_in_ == input_dim_1_ * input_dim_2_ * input_dim_3_);
        
    // output sanity checks
    KALDI_ASSERT(dim_out_ == output_dim_1_ * output_dim_2_ * output_dim_3_);

    //===============================================================//
    //                Initialize parameters                          //
    //===============================================================//
    
    //initial dimension parameters
    wei_1_i1_ = input_dim_1_; 
    wei_1_j1_ = output_dim_1_;
    wei_2_i2_ = input_dim_2_;
    wei_2_j2_ = output_dim_2_;
    wei_3_i3_ = input_dim_3_;
    wei_3_j3_ = output_dim_3_;

    //initialize weights
    Matrix<BaseFloat> mat_w1(wei_1_j1_,wei_1_i1_);
    Matrix<BaseFloat> mat_w2(wei_2_j2_,wei_2_i2_);
    Matrix<BaseFloat> mat_w3(wei_3_j3_,wei_3_i3_);
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
    for (int32 r = 0; r < wei_3_j3_; r++) {
      for (int32 c = 0; c < wei_3_i3_; c++) {
        // 0-mean Gauss with given std_dev for weight 2
        mat_w3(r, c) = param_stddev * RandGauss();
      }
    }

    mode_1_wei_ = mat_w1;     //mode 1 product weight
    mode_2_wei_ = mat_w2;     //mode 2 product weight
    mode_3_wei_ = mat_w3;     //mode 3 product weight

    //initialize bias
    Vector<BaseFloat> vec(wei_1_j1_ * wei_2_j2_ * wei_3_j3_);
    for (int32 i = 0; i < wei_1_j1_ * wei_2_j2_ * wei_3_j3_; i++) {
        // +/- 1/2*bias_range      from bias_mean:
        vec(i) = bias_mean + (RandUniform() - 0.5) * bias_range;
    }
    bias_ = vec;

    learn_rate_coef_ = learn_rate_coef;
    bias_learn_rate_coef_ = bias_learn_rate_coef;
    //
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
    ExpectToken(is, binary, "<InputDim3>");
    ReadBasicType(is, binary, &input_dim_3_);
    ExpectToken(is, binary, "<OutputDim1>");
    ReadBasicType(is, binary, &output_dim_1_);
    ExpectToken(is, binary, "<OutputDim2>");
    ReadBasicType(is, binary, &output_dim_2_);
    ExpectToken(is, binary, "<OutputDim3>");
    ReadBasicType(is, binary, &output_dim_3_);
    
    // weight dimension parameters
    ExpectToken(is, binary, "<Wei1Col>");
    ReadBasicType(is, binary, &wei_1_i1_);
    ExpectToken(is, binary, "<Wei1Row>");
    ReadBasicType(is, binary, &wei_1_j1_);
    ExpectToken(is, binary, "<Wei2Col>");
    ReadBasicType(is, binary, &wei_2_i2_);
    ExpectToken(is, binary, "<Wei2Row>");
    ReadBasicType(is, binary, &wei_2_j2_);
    ExpectToken(is, binary, "<Wei3Col>");
    ReadBasicType(is, binary, &wei_3_i3_);
    ExpectToken(is, binary, "<Wei3Row>");
    ReadBasicType(is, binary, &wei_3_j3_);


    // trainable parameters
    ExpectToken(is, binary, "<Mode1Weight>");
    mode_1_wei_.Read(is, binary);
    ExpectToken(is, binary, "<Mode2Weight>");
    mode_2_wei_.Read(is, binary);
    ExpectToken(is, binary, "<Mode3Weight>");
    mode_3_wei_.Read(is, binary);

    ExpectToken(is, binary, "<Bias>");
    bias_.Read(is, binary);
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
    WriteToken(os, binary, "<InputDim3>");
    WriteBasicType(os, binary, input_dim_3_);
    WriteToken(os, binary, "<OutputDim1>");
    WriteBasicType(os, binary, output_dim_1_);
    WriteToken(os, binary, "<OutputDim2>");
    WriteBasicType(os, binary, output_dim_2_);
    WriteToken(os, binary, "<OutputDim3>");
    WriteBasicType(os, binary, output_dim_3_);


    // weight dimension parameters
    WriteToken(os, binary, "<Wei1Col>");
    WriteBasicType(os, binary, wei_1_i1_);
    WriteToken(os, binary, "<Wei1Row>");
    WriteBasicType(os, binary, wei_1_j1_);
    WriteToken(os, binary, "<Wei2Col>");
    WriteBasicType(os, binary, wei_2_i2_);
    WriteToken(os, binary, "<Wei2Row>");
    WriteBasicType(os, binary, wei_2_j2_);
    WriteToken(os, binary, "<Wei3Col>");
    WriteBasicType(os, binary, wei_3_i3_);
    WriteToken(os, binary, "<Wei3Row>");
    WriteBasicType(os, binary, wei_3_j3_);


    // trainable parameters
    WriteToken(os, binary, "<Mode1Weight>");
    mode_1_wei_.Write(os, binary);
    WriteToken(os, binary, "<Mode2Weight>");
    mode_2_wei_.Write(os, binary);
    WriteToken(os, binary, "<Mode3Weight>");
    mode_3_wei_.Write(os, binary);

    WriteToken(os, binary, "<Bias>");
    bias_.Write(os, binary);
    
  }

  int32 NumParams() const {
    return mode_1_wei_.NumRows() * mode_1_wei_.NumCols()\
           + mode_2_wei_.NumRows() * mode_2_wei_.NumCols()\
           + mode_3_wei_.NumRows() * mode_3_wei_.NumCols()\
           + bias_.Dim(); 
  }

  void GetParams(Vector<BaseFloat>* wei_copy) const {
    //make a stack memories for all weights
    wei_copy->Resize(NumParams());
    int32 weight_1_num_elem = mode_1_wei_.NumRows() * mode_1_wei_.NumCols();
    int32 weight_2_num_elem = mode_2_wei_.NumRows() * mode_2_wei_.NumCols();
    int32 weight_3_num_elem = mode_3_wei_.NumRows() * mode_3_wei_.NumCols();
    int32 bias_num_elem = bias_.Dim();
    //Range(o,l) o:original l:length
    wei_copy->Range(0, weight_1_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(mode_1_wei_));
    wei_copy->Range(weight_1_num_elem, weight_2_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(mode_2_wei_));
    wei_copy->Range(weight_1_num_elem+weight_2_num_elem,weight_3_num_elem).CopyRowsFromMat(Matrix<BaseFloat>(mode_3_wei_));
    wei_copy->Range(weight_1_num_elem+weight_2_num_elem+weight_3_num_elem, bias_num_elem).CopyFromVec(Vector<BaseFloat>(bias_));
  }

  std::string Info() const {
    //Optionally print some additional info
    return std::string("\n  mode_1_weights") + MomentStatistics(mode_1_wei_) +
                       "\n  mode_2_weights" +  MomentStatistics(mode_2_wei_) +
                       "\n  mode_3_weights" +  MomentStatistics(mode_3_wei_) +
                       "\n  bias" + MomentStatistics(bias_);
  }
  std::string InfoGradient() const {
    //Reimplemented from Component
    return std::string("\n  mode_1_grad") + MomentStatistics(mode_1_wei_grad_) +
                       "\n  mode_2_grad" + MomentStatistics(mode_2_wei_grad_) +            
                       "\n  mode_3_grad" + MomentStatistics(mode_3_wei_grad_) +            
                       ", lr-coef " + ToString(learn_rate_coef_) +
                       "\n  bias_grad" + MomentStatistics(bias_grad_) +
                       ", lr-coef " + ToString(bias_learn_rate_coef_);
  }


  void PropagateFnc(const CuMatrixBase<BaseFloat> &in, CuMatrixBase<BaseFloat> *out) 
  { 
     //KALDI_LOG<<"tcn 3way propagate fnc is ok";
     int32 batch_size = in.NumRows();        // get batch size
     CuTensor<BaseFloat> *input = new CuTensor<BaseFloat>(in,batch_size,wei_1_i1_,wei_2_i2_,wei_3_i3_);
     CuTensor<BaseFloat> *rs_input = new CuTensor<BaseFloat>(batch_size,wei_1_i1_,wei_2_i2_,wei_3_i3_,1);
     rs_input->ReshapeFromTensor(*input,1);
     //KALDI_LOG<<"input rs type: "<<input->ReshapeType()<<" rs_input rs type: "<<rs_input->ReshapeType();
     CuTensor<BaseFloat> *mode_1_res = new CuTensor<BaseFloat>(batch_size,wei_1_j1_,wei_2_i2_,wei_3_i3_,1);
     CuTensor<BaseFloat> *mode_2_res = new CuTensor<BaseFloat>(batch_size,wei_1_j1_,wei_2_j2_,wei_3_i3_,2);
     CuTensor<BaseFloat> *mode_3_res = new CuTensor<BaseFloat>(batch_size,wei_1_j1_,wei_2_j2_,wei_3_j3_,3);
     // mode n product
     mode_1_res->mode_1_product(*rs_input,kNoTrans,mode_1_wei_,kTrans);
     mode_2_res->mode_2_product(*mode_1_res,kNoTrans,mode_2_wei_,kTrans);
     mode_3_res->mode_3_product(*mode_2_res,kNoTrans,mode_3_wei_,kTrans);
     // copy tensor result
     out->ReshapeFromTensor(*mode_3_res,30);
     // add bias
     out->AddVecToRows(1.0, bias_, 1.0);
     delete input; delete rs_input; delete mode_1_res; delete mode_2_res; delete mode_3_res;
  }


  void BackpropagateFnc(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &out,
                        const CuMatrixBase<BaseFloat> &out_diff, CuMatrixBase<BaseFloat> *in_diff)                       
  {
    //KALDI_LOG<<"tcn 3way backpropagate fnc is ok";
    int32 batch_size = out_diff.NumRows();                  //get batch size
    CuTensor<BaseFloat> outdiff(out_diff,batch_size,wei_1_j1_,wei_2_j2_,wei_3_j3_);
    CuTensor<BaseFloat> rs_outdiff(batch_size,wei_1_j1_,wei_2_j2_,wei_3_j3_,1);
    rs_outdiff.ReshapeFromTensor(outdiff,1);
    CuTensor<BaseFloat> mode_1_res(batch_size,wei_1_i1_,wei_2_j2_,wei_3_j3_,1);
    CuTensor<BaseFloat> mode_2_res(batch_size,wei_1_i1_,wei_2_i2_,wei_3_j3_,2);
    CuTensor<BaseFloat> mode_3_res(batch_size,wei_1_i1_,wei_2_i2_,wei_3_i3_,3);
    // mode n product
    mode_1_res.mode_1_product(rs_outdiff,kNoTrans,mode_1_wei_,kNoTrans);
    mode_2_res.mode_2_product(mode_1_res,kNoTrans,mode_2_wei_,kNoTrans);
    mode_3_res.mode_3_product(mode_2_res,kNoTrans,mode_3_wei_,kNoTrans);
    
    // reshaped to matrix
    in_diff->ReshapeFromTensor(mode_3_res,30);
  }

  //update back propagation
  void Update(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &diff) 
  {
    //KALDI_LOG<<"tcn 3way update is ok";
    // we use following hyperparameters from the option class
    const BaseFloat lr = opts_.learn_rate * learn_rate_coef_;
    const BaseFloat lr_bias = opts_.learn_rate * bias_learn_rate_coef_;
    const BaseFloat mmt = opts_.momentum;
    const BaseFloat l2 = opts_.l2_penalty;
    const BaseFloat l1 = opts_.l1_penalty;

    // we will also need the number of frames in the mini-batch
    const int32 batch_size = in.NumRows();
    int32 i1,i2,i3,ib,j1,j2,j3;
    i1 = wei_1_i1_; i2 = wei_2_i2_; i3 = wei_3_i3_; ib = batch_size;
    j1 = wei_1_j1_; j2 = wei_2_j2_; j3 = wei_3_j3_;

    // compute gradient
    CuTensor<BaseFloat> t_input(in,ib,i1,i2,i3);
    CuTensor<BaseFloat> t_diff(diff,ib,j1,j2,j3);
    mode_1_wei_grad_.Resize(wei_1_j1_, wei_1_i1_);             // j1*i1
    mode_2_wei_grad_.Resize(wei_2_j2_, wei_2_i2_);             // j2*i2
    mode_3_wei_grad_.Resize(wei_3_j3_, wei_3_i3_);             // j3*i3
    bias_grad_.Resize(wei_1_j1_ * wei_2_j2_ * wei_3_j3_);      // (j1*j2*j3)
    // copute w1 gradient
    {
      CuTensor<BaseFloat> *m2 = new CuTensor<BaseFloat>(ib,i1,j2,i3,0);          // (b,i1*j2*i3)
      CuTensor<BaseFloat> *m3 = new CuTensor<BaseFloat>(ib,i1,j2,j3,0);          // (b,i1*j2*j3)
      CuTensor<BaseFloat> *rs_diff = new CuTensor<BaseFloat>(ib,j1,j2,j3,1);     // (b*j2*j3,j1)
      CuTensor<BaseFloat> *rs_m1 = new CuTensor<BaseFloat>(ib,i1,j2,j3,1);       // (b*j2*j3,i1)
      m2->mode_2_product_v0(t_input,kNoTrans,mode_2_wei_,kTrans);                // (b,i1*j2*i3)
      m3->mode_3_product_v0(*m2,kNoTrans,mode_3_wei_,kTrans);                     // (b,i1*j2*j3)
      rs_diff->ReshapeFromTensor(t_diff,1);                                      // (b*j2*j3,j1) 
      rs_m1->ReshapeFromTensor(*m3,1);                                            // (b*j2*j3,i1)
      mode_1_wei_grad_.AddMatMat(1.0,*rs_diff,kTrans,*rs_m1,kNoTrans,0.0);         // (j1*i1) 
      delete m2; delete m3; delete rs_diff; delete rs_m1;
    }
    // copute w2 gradient
    {
      CuTensor<BaseFloat> *m1 = new CuTensor<BaseFloat>(ib,j1,i2,i3,0);          // (b,j1*i2*i3)
      CuTensor<BaseFloat> *m3 = new CuTensor<BaseFloat>(ib,j1,i2,j3,0);          // (b,j1*i2*j3)
      CuTensor<BaseFloat> *rs_diff = new CuTensor<BaseFloat>(ib,j1,j2,j3,2);     // (b*j1*j3,j2)
      CuTensor<BaseFloat> *rs_m2 = new CuTensor<BaseFloat>(ib,j1,i2,j3,2);       // (b*j1*j3,i2)
      m1->mode_1_product_v0(t_input,kNoTrans,mode_1_wei_,kTrans);                // (b,j1*i2*i3)
      m3->mode_3_product_v0(*m1,kNoTrans,mode_3_wei_,kTrans);                     // (b,j1*i2*j3)
      rs_diff->ReshapeFromTensor(t_diff,2);                                      // (b*j1*j3,j2) 
      rs_m2->ReshapeFromTensor(*m3,2);                                            // (b*j1*j3,i2)
      mode_2_wei_grad_.AddMatMat(1.0,*rs_diff,kTrans,*rs_m2,kNoTrans,0.0);         // (j2*i2) 
      delete m1; delete m3; delete rs_diff; delete rs_m2;
    }
    // copute w3 gradient
    {
      CuTensor<BaseFloat> *m1 = new CuTensor<BaseFloat>(ib,j1,i2,i3,0);          // (b,j1*i2*i3)
      CuTensor<BaseFloat> *m2 = new CuTensor<BaseFloat>(ib,j1,j2,i3,0);          // (b,j1*j2*i3)
      CuTensor<BaseFloat> *rs_diff = new CuTensor<BaseFloat>(ib,j1,j2,j3,3);     // (b*j1*j2,j3)
      CuTensor<BaseFloat> *rs_m3 = new CuTensor<BaseFloat>(ib,j1,j2,i3,3);       // (b*j1*j2,i3)
      m1->mode_1_product_v0(t_input,kNoTrans,mode_1_wei_,kTrans);                // (b,j1*i2*i3)
      m2->mode_2_product_v0(*m1,kNoTrans,mode_2_wei_,kTrans);                     // (b,j1*i2*j3)
      rs_diff->ReshapeFromTensor(t_diff,3);                                      // (b*j1*j2,j3) 
      rs_m3->ReshapeFromTensor(*m2,3);                                            // (b*j1*j2,i3)
      mode_3_wei_grad_.AddMatMat(1.0,*rs_diff,kTrans,*rs_m3,kNoTrans,0.0);         // (j3*i3) 
      delete m1; delete m2; delete rs_diff; delete rs_m3;
    }
        

    // bias
    bias_grad_.AddRowSumMat(1.0, diff, 0.0);
    // update
    mode_1_wei_.AddMat(-lr,mode_1_wei_grad_);
    mode_2_wei_.AddMat(-lr,mode_2_wei_grad_);
    mode_3_wei_.AddMat(-lr,mode_3_wei_grad_);
    bias_.AddVec(-lr_bias, bias_grad_);

   }

  const CuMatrixBase<BaseFloat>& GetCuMatrixBase(CuMatrix<BaseFloat>& cumatrix)
  {
    return cumatrix;
  }


 private:
  int32 wei_1_i1_,wei_1_j1_,       //weight 1 dimensions for input data row
        wei_2_i2_,wei_2_j2_,       //weight 2 dimensions for input data column
        wei_3_i3_,wei_3_j3_;       //weight 3 dimensions for input data column

  int32 input_dim_1_,input_dim_2_,input_dim_3_;       //input matrix dimension
  int32 output_dim_1_,output_dim_2_,output_dim_3_;    //output matrix dimension
  int32 dim_in_,dim_out_;                             //these two parameter is used for checking

  BaseFloat learn_rate_coef_;
  BaseFloat bias_learn_rate_coef_;

  //weight of mode 1 2 product and bias
  CuMatrix<BaseFloat> mode_1_wei_;           //j1*i1
  CuMatrix<BaseFloat> mode_2_wei_;           //j2*i2
  CuMatrix<BaseFloat> mode_3_wei_;           //j3*i3
  CuVector<BaseFloat> bias_;                 //(j1*j2*j3)

  //gradient of mode 1 2 product and bias
  CuMatrix<BaseFloat>  mode_1_wei_grad_;
  CuMatrix<BaseFloat>  mode_2_wei_grad_;
  CuMatrix<BaseFloat>  mode_3_wei_grad_;
  CuVector<BaseFloat>  bias_grad_;

};

}  // namespace nnet1
}  // namespace kaldi

#endif
