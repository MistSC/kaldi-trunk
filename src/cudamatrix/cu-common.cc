// cudamatrix/cu-common.cc

// Copyright      2013  Karel Vesely
//                2015  Johns Hopkins University (author: Daniel Povey)

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

#ifndef KALDI_CUDAMATRIX_COMMON_H_
#define KALDI_CUDAMATRIX_COMMON_H_

// This file contains some #includes, forward declarations
// and typedefs that are needed by all the main header
// files in this directory.
#include "base/kaldi-common.h"
#include "matrix/kaldi-blas.h"
#include "cudamatrix/cu-device.h"
#include "cudamatrix/cu-common.h"
#include "cudamatrix/cu-matrixdim.h"

namespace kaldi {

#if HAVE_CUDA == 1
cublasOperation_t KaldiTransToCuTrans(MatrixTransposeType kaldi_trans) {
  cublasOperation_t cublas_trans;

  if (kaldi_trans == kNoTrans)
    cublas_trans = CUBLAS_OP_N;
  else if (kaldi_trans == kTrans)
    cublas_trans = CUBLAS_OP_T;
  else
    cublas_trans = CUBLAS_OP_C;
  return cublas_trans;
}

void GetBlockSizesForSimpleMatrixOperation(int32 num_rows,
                                           int32 num_cols,
                                           dim3 *dimGrid,
                                           dim3 *dimBlock) {
  KALDI_ASSERT(num_rows > 0 && num_cols > 0);
  int32 col_blocksize = 64, row_blocksize = 4;
  while (col_blocksize > 1 &&
         (num_cols + (num_cols / 2) <= col_blocksize ||
          num_rows > 65536 * row_blocksize)) {
    col_blocksize /= 2;
    row_blocksize *= 2;
  }

  dimBlock->x = col_blocksize;
  dimBlock->y = row_blocksize;
  dimBlock->z = 1;
  dimGrid->x = n_blocks(num_cols, col_blocksize);
  dimGrid->y = n_blocks(num_rows, row_blocksize);
  KALDI_ASSERT(dimGrid->y <= 65536 &&
               "Matrix has too many rows to process");
  dimGrid->z = 1;
}

void GetBlockSizesForSimpleTensorOperation(int32 ib,
                                           int32 i1,
                                           int32 i2,
                                           int32 i3,
                                           dim3 *dimGrid,
                                           dim3 *dimBlock) {
  //KALDI_ASSERT(ib > 0 && i1 > 0 && i2 > 0 && i3 > 0);
  //int32 num_i1 = 16, num_i2 = 16, num_i3 = 16, num_ib = 16;
  //KALDI_LOG<<"ib: "<<ib<<" i1: "<<i1<<" i2: "<<i2<<" i3: "<<i3;
  int gridx, gridy, gridz;
  dimBlock->x = 16;
  dimBlock->y = 8;
  dimBlock->z = 8;
  gridx = 2;
  gridy = 2;
  gridz = 2;
  KALDI_LOG<<"gridx: "<<gridx<<" gridy: "<<gridy<<" gridz: "<<gridz;
  while(dimBlock->x*gridx < ib)
    gridx *= 2;
  while(dimBlock->y*gridy < i1)
    gridy *= 2;
  while(dimBlock->z*gridz < i2*i3)
    gridz *= 2;
  KALDI_LOG<<"gridx: "<<gridx<<" gridy: "<<gridy<<" gridz: "<<gridz;
  dimGrid->x = gridx;
  dimGrid->y = gridy;
  dimGrid->z = gridz;
}
#endif

} // namespace


#endif  // KALDI_CUDAMATRIX_COMMON_H_
