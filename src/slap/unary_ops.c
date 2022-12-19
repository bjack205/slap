//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "unary_ops.h"

#include "matrix_checks.h"

enum slap_ErrorCode slap_SetConst(Matrix mat, double val) {
  SLAP_CHECK_MATRIX(mat);
  int num_el = slap_NumElements(mat);
  for (int i = 0; i < num_el; ++i) {
    mat.data[i] = val;
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_SetIdentity(Matrix mat, double val) {
  SLAP_CHECK_MATRIX(mat);
  slap_SetConst(mat, 0.0);
  for (int i = 0; i < slap_MinDim(mat); ++i) {
    slap_SetElement(mat, i, i, val);
  }
  return 0;
}

enum slap_ErrorCode slap_ScaleByConst(Matrix mat, double alpha) {
  SLAP_CHECK_MATRIX(mat);
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    mat.data[i] *= alpha;
  }
  return 0;
}

/**
 * @brief Set the first n elements of a matrix diagonal from an array
 *
 * If @a len is greater than the minimum dimension, only the minimum dimension will be set.
 * Doesn't touch any of the off-diagonal elements.
 *
 * @param mat Matrix (nrows >= ncols)
 * @param diag Array of length `nrows`.
 * @return
 */
enum slap_ErrorCode slap_SetDiagonal(Matrix mat, const double* diag, int len);

