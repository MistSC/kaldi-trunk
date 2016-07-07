// nnet/nnet-tcn.h

#ifndef KALDI_NNET_NNET_OUTER_PRODUCT_H_
#define KALDI_NNET_NNET_OUTER_PRODUCT_H_

#include <iostream>
#include <vector>
#include "nnet/nnet-component.h"
#include "nnet/nnet-various.h"
#include "cudamatrix/cu-math.h"

namespace kaldi {
namespace nnet1 {
class OPComponent : public UpdatableComponent {
 public:
 OPComponent(int32 dim_in,int32 dim_out)
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
      if (token == "<InputDim1>")            ReadBasicType(is, false, &input_dim_1_);
      else if (token == "<InputDim2>")       ReadBasicType(is, false, &input_dim_2_);
      else if (token == "<OutputDim1>")      ReadBasicType(is, false, &output_dim_1_);
      else if (token == "<OutputDim2>")      ReadBasicType(is, false, &output_dim_2_);
      //else if (token == "<LearnRateCoef>") ReadBasicType(is, false, &learn_rate_coef);
      //else if (token == "<BiasLearnRateCoef>") ReadBasicType(is, false, &bias_learn_rate_coef);
      else KALDI_ERR << "Unknown token " << token << ", a typo in config?"
                     << " (ParamStddev|BiasMean|BiasRange|FmapXLen|FmapYLen|FiltXLen|FiltYLen|FiltXStep|FiltYStep|ConnectFmap|LearnRateCoef|BiasLearnRateCoef)";
      is >> std::ws;  // eat-up whitespace
    }

  }

  void ReadData(std::istream &is, bool binary) {
    // input output dimension parameters
    ExpectToken(is, binary, "<InputDim1>");
    ReadBasicType(is, binary, &input_dim_1_);
    ExpectToken(is, binary, "<InputDim2>");
    ReadBasicType(is, binary, &input_dim_2_);
    ExpectToken(is, binary, "<OutputDim1>");
    ReadBasicType(is, binary, &output_dim_1_);
    ExpectToken(is, binary, "<OutputDim2>");
    ReadBasicType(is, binary, &output_dim_2_);
  }

  void WriteData(std::ostream &os, bool binary) const {
    // input output dimension parameters
    WriteToken(os, binary, "<InputDim1>");
    WriteBasicType(os, binary, input_dim_1_);
    WriteToken(os, binary, "<InputDim2>");
    WriteBasicType(os, binary, input_dim_2_);
    WriteToken(os, binary, "<OutputDim1>");
    WriteBasicType(os, binary, output_dim_1_);
    WriteToken(os, binary, "<OutputDim2>");
    WriteBasicType(os, binary, output_dim_2_);
  }

  int32 NumParams() const {
    return;
  }

  void GetParams(Vector<BaseFloat>* wei_copy) const {
    //make a stack memories for all weights
  }

  std::string Info() const {
    //Optionally print some additional info
    return;
  }
  std::string InfoGradient() const {
    //Reimplemented from Component
    return;
  }
  
  void PropagateFnc(const CuMatrixBase<BaseFloat> &in, CuMatrixBase<BaseFloat> *out) 
  {
    Matrix<BaseFloat> A(in);
    Matrix<BaseFloat> B(A);
    Matrix<BaseFloat> C;
    C.OuterProductForEachFrame(1.0, A, B);
    out.CopyFromMat(C);
  }


  void BackpropagateFnc(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &out,
                        const CuMatrixBase<BaseFloat> &out_diff, CuMatrixBase<BaseFloat> *in_diff)                       
  {
  }

  void Update(const CuMatrixBase<BaseFloat> &in, const CuMatrixBase<BaseFloat> &diff) 
  {
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

};

}  // namespace nnet1
}  // namespace kaldi

#endif
