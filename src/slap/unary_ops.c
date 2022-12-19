//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "unary_ops.h"

#include "matrix_checks.h"
#include "iterator.h"

enum slap_ErrorCode slap_SetConst(Matrix mat, double val) {
  SLAP_CHECK_MATRIX(mat);
  for (MatrixIterator it = slap_Iterator(mat); !slap_IsFinished(&it); slap_Step(&it)) {
    mat.data[it.index] = val;
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_ScaleByConst(Matrix mat, double alpha) {
  SLAP_CHECK_MATRIX(mat);
  for (MatrixIterator it = slap_Iterator(mat); !slap_IsFinished(&it); slap_Step(&it)) {
    mat.data[it.index] *= alpha;
  }
  return 0;
}

enum slap_ErrorCode slap_SetIdentity(Matrix mat, double val) {
  SLAP_CHECK_MATRIX(mat);
  slap_SetConst(mat, 0.0);
  for (int k = 0; k < slap_MinDim(mat); ++k) {
    slap_SetElement(mat, k, k, val);
  }
  return 0;
}


enum slap_ErrorCode slap_SetDiagonal(Matrix mat, const double* diag, int len) {
  int n = slap_MinDim(mat);
  n = n <= len ? n : len;
  for (int k = 0; k < n; ++k) {
    slap_SetElement(mat, k, k, diag[k]);
  }
  return SLAP_NO_ERROR;
}
