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
  SLAP_CHECK_MATRIX(mat);
  int n = slap_MinDim(mat);
  n = n <= len ? n : len;
  for (int k = 0; k < n; ++k) {
    slap_SetElement(mat, k, k, diag[k]);
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_AddIdentity(Matrix mat, double alpha) {
  SLAP_CHECK_MATRIX(mat);
  int n = slap_MinDim(mat);
  for (int i = 0; i < n; ++i) {
    double diag = *slap_GetElement(mat, i, i);
    slap_SetElement(mat, i, i, diag + alpha);
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_SetRange(Matrix mat, double start, double stop) {
  SLAP_CHECK_MATRIX(mat);
  double range = stop - start;
  double num_el = slap_NumElements(mat) - 1;
  double step = range / num_el;
  // NOTE: Don't use iterator here since iteration order matters
  int k = 0;
  for (int j = 0; j < slap_NumCols(mat); ++j) {
    for (int i = 0; i < slap_NumRows(mat); ++i) {
      slap_SetElement(mat, i, j, start + k * step);
      ++k;
    }
  }
  return SLAP_NO_ERROR;
}
