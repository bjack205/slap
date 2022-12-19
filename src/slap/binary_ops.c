//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "binary_ops.h"

#include <math.h>

#include "matrix_checks.h"

double slap_MatrixNormedDifference(const Matrix A, const Matrix B) {
  SLAP_CHECK_MATRIX(A);
  SLAP_CHECK_MATRIX(B);
  if (!A.data || !B.data) {
    return INFINITY;
  }
  if ((A.rows != B.rows) || (A.cols != B.cols)) {
    fprintf(stderr, "Can't compare matrices of different sizes. Got (%d,%d) and (%d,%d)\n",
            A.rows, A.cols, B.rows, B.cols);
    return INFINITY;
  }

  double diff = 0;
  for (int i = 0; i < slap_NumElements(A); ++i) {
    double d = A.data[i] - B.data[i];
    diff += d * d;
  }
  return sqrt(diff);
}
enum slap_ErrorCode slap_MatAdd(Matrix C, const Matrix A, const Matrix B, double alpha) {
  SLAP_CHECK_MATRIX(A);
  SLAP_CHECK_MATRIX(B);
  SLAP_CHECK_MATRIX(C);
  int n = slap_NumRows(C);
  int m = slap_NumCols(C);
  if (slap_NumRows(A) != n || slap_NumCols(A) != m || slap_NumRows(B) != n ||
      slap_NumCols(B) != m) {
    char msg[80];
    sprintf(msg, "Cannot add matrices with sizes (%d,%d), (%d,%d) -> (%d,%d)",
            slap_NumRows(A), slap_NumCols(A), slap_NumRows(B), slap_NumCols(B),
            slap_NumRows(C), slap_NumCols(C));
    return SLAP_THROW_ERROR(SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS, msg);
  }
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      double Aij = *slap_GetElementConst(A, i, j);
      double Bij = *slap_GetElementConst(B, i, j);
      slap_SetElement(C, i, j, Aij + alpha * Bij);
    }
  }
  return SLAP_NO_ERROR;
}
