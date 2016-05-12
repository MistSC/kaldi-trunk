// cudamatrix/cu-matrix-inl.h

// Copyright 2009-2012  Karel Vesely

// See ../../COPYING for clarification regarding multiple authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.

// Do not include this file directly.  It is included by cu-matrix.h.

#ifndef KALDI_CUDAMATRIX_CU_MATRIX_INL_H_
#define KALDI_CUDAMATRIX_CU_MATRIX_INL_H_

namespace kaldi {

template<typename Real>
inline CuSubMatrix<Real>::CuSubMatrix(const CuMatrixBase<Real> &mat,
                                      const MatrixIndexT row_offset,
                                      const MatrixIndexT num_rows,
                                      const MatrixIndexT col_offset,
                                      const MatrixIndexT num_cols) {
  if (num_rows == 0 || num_cols == 0) {
    KALDI_ASSERT(num_rows == 0 && num_cols == 0);
    // Everything will have been set to zero in CuMastrixBase's default
    // initializer, so nothing to do.
  } else {
    KALDI_ASSERT(row_offset >= 0 && col_offset >= 0 &&
                 row_offset + num_rows <= mat.num_rows_ &&
                 col_offset + num_cols <= mat.num_cols_);
    this->data_ = mat.data_ + (row_offset * mat.stride_) + col_offset;
    this->num_cols_ = num_cols;
    this->num_rows_ = num_rows;
    this->stride_ = mat.stride_;
  }
}

template<typename Real>
inline CuSubMatrix<Real>::CuSubMatrix(const Real *data,
                                      const MatrixIndexT num_rows,
                                      const MatrixIndexT num_cols,
                                      const MatrixIndexT stride):
    CuMatrixBase<Real>(const_cast<Real*>(data), num_rows, num_cols, stride) {
  // in general if you use SubMatrix or CuSubMatrix, const-correctness is not
  // preserved (preserving it would require us duplicating the class and it
  // would have been a hassle).
  KALDI_ASSERT((num_rows != 0) == (num_cols != 0) && stride >= 0 &&
               num_rows >= 0 && num_cols >= 0 && num_cols <= stride);
}

// sc function
// this constructor used for getting the reshaped matrix of one input vector
// another constructer if cusubmatrx
// it's a kind of reshape
template<typename Real>
inline CuSubMatrix<Real>::CuSubMatrix(const CuMatrixBase<Real> &mat,
                                      const MatrixIndexT batch_index,
                                      const MatrixIndexT num_rows,
                                      const MatrixIndexT num_cols)
{
  if (num_rows == 0 || num_cols == 0)
  {
    KALDI_ASSERT(num_rows == 0 && num_cols == 0);
    // Everything will have been set to zero in CuMastrixBase's default
    // initializer, so nothing to do.
  }
  else
  {
    KALDI_ASSERT(num_cols > 0 && num_rows > 0 &&
                 batch_index >= 0 &&
                 batch_index <= mat.num_rows_ &&
                 num_cols * num_rows == mat.num_cols_ &&
                 num_cols * num_rows <= mat.stride_);
    this->data_ = mat.data_ + batch_index * mat.stride_;
    this->num_cols_ = num_cols;
    this->num_rows_ = num_rows;
    // stride: memory distance between each rows
    // stride >= cols
    this->stride_ = num_cols;
  }
}                            


// Constructor... note that this is not const-safe as it would
// be quite complicated to implement a "const Tensor" class that
// would not allow its contents to be changed.
/*
template<typename Real>
inline CuTensor<Real>::CuTensor(const CuMatrixBase<Real> &mat,
                                const MatrixIndexT batch_size,
                                const MatrixIndexT num_i1,
                                const MatrixIndexT num_i2,
                                const MatrixIndexT num_i3)
{
  if (num_i1 == 0 || num_i2 == 0 || num_i3 == 0 || batch_size == 0)
  {
    KALDI_ASSERT(num_i1 == 0 && num_i2 == 0 && num_i3 == 0 && batch_size == 0);
    // Everything will have been set to zero in CuMastrixBase's default
    // initializer, so nothing to do.
  }
  else
  {
    KALDI_ASSERT(mat.num_cols_ == num_i1*num_i2*num_i3 &&
                 mat.num_rows_ == batch_size);
    this->data_ = mat.data_;

    this->num_cols_ = mat.num_cols_;
    this->num_rows_ = mat.num_rows_;
    this->stride_ = mat.Stride();

    this->batch_size_ = batch_size;
    this->num_i1_ = num_i1;
    this->num_i2_ = num_i2;
    this->num_i3_ = num_i3;
  }
}
*/



/*
// reshape tensor to a special matrix
template<typename Real>
inline void CuTensor<Real>::ReshapeToMatrix(MatrixBase<Real> *M,
                                            MatrixIndexT mode)
{
  KALDI_ASSERT(M->NumRows() >=0 && M->NumCols() >= 0 && mode >= 0 && mode <= 3 &&
               M->NumRows() * M->NumCols() ==
               this->num_i1_ * this->num_i2_ * this->num_i3_ * this->batch_size_);
  KALDI_LOG<<M->NumRows()<<"  "<<M->NumCols()<<"  "<<M->Stride();
#if HAVE_CUDA == 1
  if (CuDevice::Instantiate().Enabled())
  {
    Timer tim;
    dim3 dimBlock(CU2DBLOCK, CU2DBLOCK);
    dim3 dimGrid(n_blocks(this->num_cols_, CU2DBLOCK),
                 n_blocks(this->num_rows_, CU2DBLOCK));
    switch(mode)
    {
      case 1:
        // M(l*i2*i3,i1)
        KALDI_ASSERT(M->NumCols() == this->num_i1_);
        cuda_resape_to_matrix(dimGrid, dimBlock, M->Data(), this->data_, M->Dim(), this->TDim(), mode);
        //cuda_copy_to_rows(dimGrid, dimBlock, dst.Data(), data_, Dim());
    }
    CU_SAFE_CALL(cudaGetLastError());
    CuDevice::Instantiate().AccuProfile(__func__, tim.Elapsed());
  } else
#endif
  {
  }
}
*/

} // namespace kaldi

#endif


