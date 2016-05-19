// nnet/nnet-tcn-projection.h

#ifndef KALDI_NNET_NNET_TCN_PROJECTION_3WAY_H_
#define KALDI_NNET_NNET_TCN_PROJECTION_3WAY_H_


#include <vector>
#include <string>
#include <sstream>
#include "nnet/nnet-component.h"
#include "nnet/nnet-utils.h"
#include "cudamatrix/cu-math.h"

namespace kaldi {
namespace nnet1 {
class TCN3WayProjectionComponent : public UpdatableComponent {
  public:
  TCN3WayProjectionComponent(int32 dim_in, int32 dim_out)
    : UpdatableComponent(dim_in, dim_out),
      //initial dimension parameters
      wei_dim_1_(0.0),wei_dim_2_(0.0),wei_dim_3_(0.0),wei_dim_4_(0.0),
      input_dim_1_(0.0),input_dim_2_(0.0),input_dim_3_(0.0),
      dim_in_(dim_in), dim_out_(dim_out),
      //initial learning rate
      learn_rate_coef_(1.0), bias_learn_rate_coef_(1.0)
  { }
  ~TCN3WayProjectionComponent()
  { }

  Component* Copy() const { return new TCN3WayProjectionComponent(*this); }
  ComponentType GetType() const { return scTCN3WayProjectionComponent; }
  
  
  void InitData(std::istream &is) {
    // define options
    float bias_mean = -2.0, bias_range = 2.0, param_stddev = 0.1;
    float learn_rate_coef = 1.0, bias_learn_rate_coef = 1.0;
    // parse config
    std::string token; 
    while (!is.eof()) {
      ReadToken(is, false, &token); 
      if (token == "<BiasMean>")    ReadBasicType(is, false, &bias_mean);
      else if (token == "<BiasRange>")   ReadBasicType(is, false, &bias_range);
      else if (token == "<ParamStddev>") ReadBasicType(is, false, &param_stddev);
      else if (token == "<InputDim1>") ReadBasicType(is, false, &input_dim_1_);
      else if (token == "<InputDim2>") ReadBasicType(is, false, &input_dim_2_);
      else if (token == "<InputDim3>") ReadBasicType(is, false, &input_dim_3_);
      else KALDI_ERR << "Unknown token " << token << ", a typo in config?"
                     << " (ParamStddev|BiasMean|BiasRange|LearnRateCoef|BiasLearnRateCoef)";
      is >> std::ws; // eat-up whitespace
    }


    /* 
    KALDI_LOG<< "===================tokening is over==================";
    KALDI_LOG<< "BiasMean: " << bias_mean;
    KALDI_LOG<< "BiasRange: " << bias_range;
    KALDI_LOG<< "ParamStddev: " << param_stddev;
    KALDI_LOG<< "dim_in_: " << dim_in_;
    KALDI_LOG<< "dim_out_ " << dim_out_;
    //KALDI_LOG<< "input_dim_: " << input_dim_;
    //KALDI_LOG<< "output_dim_: " << output_dim_;
    KALDI_LOG<< "input dimension for way 1: " << input_dim_1_;
    KALDI_LOG<< "input dimension for way 2: " << input_dim_2_;
    */

    //===============================================================//
    //                      Sanity checks:                           //
    //===============================================================//
    // input sanity checks
    KALDI_ASSERT(dim_in_ == input_dim_1_ * input_dim_2_ * input_dim_3_);
    // output sanity checks
    //KALDI_ASSERT(dim_out_);

    //===============================================================//
    //                Initialize parameters                          //
    //===============================================================//
    //initial dimension parameters
    wei_dim_1_ = input_dim_1_;
    wei_dim_2_ = input_dim_2_;
    wei_dim_3_ = input_dim_3_;
    wei_dim_4_ = dim_out_;

    //initialize weights
    Matrix<BaseFloat>  mat(wei_dim_4_,wei_dim_1_ * wei_dim_2_ * wei_dim_3_); //initial to 0
    for (int32 i=0; i<wei_dim_4_; i++) {
      for (int32 j=0; j<wei_dim_1_ * wei_dim_2_ * wei_dim_3_; j++) {
          mat(i,j) = param_stddev * RandGauss(); // 0-mean Gauss with given std_dev
      }
    }
    weight_ = mat;
    //initial bias
    Vector<BaseFloat> vec(wei_dim_4_);
    for (int32 i=0; i<wei_dim_4_; i++)
    {
      vec(i) = bias_mean + (RandUniform() - 0.5) * bias_range;
    }
    bias_ = vec;
    //initial learning rate
    learn_rate_coef_ = learn_rate_coef;
    bias_learn_rate_coef_ = bias_learn_rate_coef;
    //
  }

  void ReadData(std::istream &is, bool binary) {
    // optional learning-rate coefs
    ExpectToken(is, binary, "<LearnRateCoef>");
    ReadBasicType(is, binary, &learn_rate_coef_);
    ExpectToken(is, binary, "<BiasLearnRateCoef>");
    ReadBasicType(is, binary, &bias_learn_rate_coef_);
    // dimensions of weights and bias
    ExpectToken(is, binary, "<InputDim1>");
    ReadBasicType(is, binary, &input_dim_1_);
    ExpectToken(is, binary, "<InputDim2>");
    ReadBasicType(is, binary, &input_dim_2_);
    ExpectToken(is, binary, "<InputDim3>");
    ReadBasicType(is, binary, &input_dim_3_);
    ExpectToken(is, binary, "<OutputDim>");
    ReadBasicType(is, binary, &dim_out_);
    // weights dimension parameters
    ExpectToken(is, binary, "<WeightDim1>");
    ReadBasicType(is, binary, &wei_dim_1_);
    ExpectToken(is, binary, "<WeightDim2>");
    ReadBasicType(is, binary, &wei_dim_2_);
    ExpectToken(is, binary, "<WeightDim3>");
    ReadBasicType(is, binary, &wei_dim_3_);
    ExpectToken(is, binary, "<WeightDim4>");
    ReadBasicType(is, binary, &wei_dim_4_);

    // weights and bias
    //give size to weights
    ExpectToken(is, binary, "<Weight>");
    weight_.Read(is, binary);
    ExpectToken(is, binary, "<Bias>");
    bias_.Read(is, binary);

  }

  void WriteData(std::ostream &os, bool binary) const {
    WriteToken(os, binary, "<LearnRateCoef>");
    WriteBasicType(os, binary, learn_rate_coef_);
    WriteToken(os, binary, "<BiasLearnRateCoef>");
    WriteBasicType(os, binary, bias_learn_rate_coef_);
    // dimensions of weight and bias
    WriteToken(os, binary, "<InputDim1>");
    WriteBasicType(os, binary, input_dim_1_);
    WriteToken(os, binary, "<InputDim2>");
    WriteBasicType(os, binary, input_dim_2_);
    WriteToken(os, binary, "<InputDim3>");
    WriteBasicType(os, binary, input_dim_3_);
    WriteToken(os, binary, "<OutputDim>");
    WriteBasicType(os, binary, dim_out_);
    // weights dimension parameters
    WriteToken(os, binary, "<WeightDim1>");
    WriteBasicType(os, binary, wei_dim_1_);
    WriteToken(os, binary, "<WeightDim2>");
    WriteBasicType(os, binary, wei_dim_2_);
    WriteToken(os, binary, "<WeightDim3>");
    WriteBasicType(os, binary, wei_dim_3_);
    WriteToken(os, binary, "<WeightDim4>");
    WriteBasicType(os, binary, wei_dim_4_);

    // weights and bias
    WriteToken(os, binary, "<Weight>");
    weight_.Write(os, binary);
    WriteToken(os, binary, "<Bias>");
    bias_.Write(os, binary);
  }


  //get parameters of weight
  int32 NumParams() const { return wei_dim_1_ * wei_dim_2_ * wei_dim_3_ * wei_dim_4_ + bias_.Dim(); }
  
  void GetParams(Vector<BaseFloat>* wei_copy) const 
  {
    //make a stack memories for all weights
    wei_copy->Resize(NumParams());
    int32 weight_elem = weight_.NumRows() * weight_.NumCols();
    //Range(o,l) o:original l:length
    wei_copy->Range(0, weight_elem).CopyRowsFromMat(Matrix<BaseFloat>(weight_));
    wei_copy->Range(weight_elem, bias_.Dim()).CopyFromVec(Vector<BaseFloat>(bias_));
  }
  
  std::string Info() const {
    return std::string("\n weights" + MomentStatistics(weight_) + 
           "\n bias" + MomentStatistics(bias_));
  }

  std::string InfoGradient() const {
    return std::string("\n weights grad" + MomentStatistics(weight_grad_) +     
           "\n bias grad" + MomentStatistics(weight_grad_));
  }

  
  // in: batch * (i1*i2*i3)
  // weight_ : i4*(i1*i2*i3)
  void PropagateFnc(const CuMatrixBase<BaseFloat> &in, CuMatrixBase<BaseFloat> *out)
  {
    //KALDI_LOG<<"tcn 3 way projection propagate fnc is ok";
    //KALDI_LOG<<"in info: "<<"num rows: "<<in.NumRows()<<" num cols: "<<in.NumCols();
    //KALDI_LOG<<"weight_ info: "<<"num rows: "<<weight_.NumRows()<<" num cols: "<<weight_.NumCols();
    // propagate
    out->AddMatMat(1.0, in, kNoTrans, weight_, kTrans, 0.0);
    // add bias
    out->AddVecToRows(1.0, bias_, 1.0);
  }

  void BackpropagateFnc(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &out,
                        const CuMatrixBase<BaseFloat> &out_diff, CuMatrixBase<BaseFloat> *in_diff) 
  {
    //KALDI_LOG<<"tcn 3 way projection backpropagate fnc is ok";
    //KALDI_LOG<<"out info: "<<"num rows: "<<out.NumRows()<<" num cols: "<<out.NumCols();

    // multiply error derivative by weights
    in_diff->AddMatMat(1.0, out_diff, kNoTrans, weight_, kNoTrans, 0.0);  
  }


  void Update(const CuMatrixBase<BaseFloat> &input, const CuMatrixBase<BaseFloat> &diff)
  {
    //KALDI_LOG<<"tcn 3 way projection update is ok";
    // initial gradient parameters
    weight_grad_.Resize(wei_dim_4_, wei_dim_1_ * wei_dim_2_ * wei_dim_3_);
    bias_grad_.Resize(wei_dim_4_);
    // we use following hyperparameters from the option class
    const BaseFloat lr = opts_.learn_rate * learn_rate_coef_;
    const BaseFloat lr_bias = opts_.learn_rate * bias_learn_rate_coef_;
    //const BaseFloat mmt = opts_.momentum;
    //const BaseFloat l2 = opts_.l2_penalty;
    //const BaseFloat l1 = opts_.l1_penalty;

    // we will also need the number of frames in the mini-batch
    const int32 batch_size = input.NumRows();

    // compute gradient
    //KALDI_LOG<<"diff info: "<<"num rows: "<<diff.NumRows()<<" num cols: "<<diff.NumCols();
    //KALDI_LOG<<"input info: "<<"num rows: "<<input.NumRows()<<" num cols: "<<input.NumCols();
    weight_grad_.AddMatMat(1.0, diff, kTrans, input, kNoTrans, 0.0);
    bias_grad_.AddRowSumMat(1.0, diff, 0.0);
    // l2 regularization
    /*
    if (l2 != 0.0)
    {
        weight_.AddMat(-lr*l2*batch_size, weight_);
    }
    if (l1 != 0.0)
    {
        cu::RegularizeL1(&weight_, &weight_grad_, lr*l1*batch_size, lr);
    }
    */
    //update
    weight_.AddMat(-lr, weight_grad_);
    bias_.AddVec(-lr_bias, bias_grad_);
  }


 private:
  int32 dim_in_,dim_out_;  //these 2 parameters are used for checking
  int32 wei_dim_1_,wei_dim_2_,wei_dim_3_,wei_dim_4_;
  int32 input_dim_1_,input_dim_2_,input_dim_3_;
  //int32 output_dim_;
  
  CuMatrix<BaseFloat> weight_;        //i4 * (i1 * i2 * i3)
  CuMatrix<BaseFloat> weight_grad_;   //i4 * (i1 * i2 * i3)

  CuVector<BaseFloat> bias_;          //i4 
  CuVector<BaseFloat> bias_grad_;     //i4

  BaseFloat learn_rate_coef_;
  BaseFloat bias_learn_rate_coef_;
};

} // namespace nnet1
} // namespace kaldi

#endif
