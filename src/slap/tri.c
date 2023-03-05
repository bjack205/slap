//
// Created by Brian Jackson on 3/4/23.
// Copyright (c) 2023 Robotic Exploration Lab. All rights reserved.
//

#include "tri.h"

#include <math.h>

enum slap_ErrorCode slap_UpperTriMulAdd(Matrix C, const Matrix U, const Matrix B,
                                        double alpha, double beta) {
  SLAP_ASSERT_VALID(C, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid C matrix");
  SLAP_ASSERT_VALID(U, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid U matrix");
  SLAP_ASSERT_VALID(B, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid B matrix");
  SLAP_ASSERT(slap_NumRows(U) == slap_NumRows(U), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Rows of C (%d) not equal to Rows of U (%d).",
              slap_NumRows(C), slap_NumRows(U));
  SLAP_ASSERT(slap_NumCols(U) == slap_NumRows(B), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Columns of U (%d) not equal to Rows of B (%d).",
              slap_NumCols(U), slap_NumRows(B));
  SLAP_ASSERT(slap_NumCols(C) == slap_NumCols(B), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Columns of C (%d) not equal to Columns of B (%d).",
              slap_NumCols(C), slap_NumCols(B));
  int m = slap_NumRows(U);
  int n = slap_NumCols(U);
  int p = slap_NumCols(B);
  if (m > n) {
    m = n;
  }
  for (int j = 0; j < p; ++j) {
    for (int i = 0; i < m; ++i) {
      sfloat* Cij = slap_GetElement(C, i, j);
      *Cij *= beta;
      for (int k = i; k < n; ++k) {
        sfloat Uik = *slap_GetElementConst(U, i, k);
        sfloat Bkj = *slap_GetElementConst(B, k, j);
        *Cij += alpha * Uik * Bkj;
      }
    }
  }
  return SLAP_NO_ERROR;
}
enum slap_ErrorCode slap_LowerTriMulAdd(Matrix C, const Matrix U, const Matrix B,
                                        double alpha, double beta) {
  SLAP_ASSERT_VALID(C, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid C matrix");
  SLAP_ASSERT_VALID(U, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid U matrix");
  SLAP_ASSERT_VALID(B, SLAP_INVALID_MATRIX, "Error in UpperTriMulAdd: Invalid B matrix");
  SLAP_ASSERT(slap_NumRows(U) == slap_NumRows(U), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Rows of C (%d) not equal to Rows of U (%d).",
              slap_NumRows(C), slap_NumRows(U));
  SLAP_ASSERT(slap_NumCols(U) == slap_NumRows(B), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Columns of U (%d) not equal to Rows of B (%d).",
              slap_NumCols(U), slap_NumRows(B));
  SLAP_ASSERT(slap_NumCols(C) == slap_NumCols(B), SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
              "Error in UpperTriMulAdd: Columns of C (%d) not equal to Columns of B (%d).",
              slap_NumCols(C), slap_NumCols(B));
  int m = slap_NumRows(U);
  int n = slap_NumCols(U);
  int p = slap_NumCols(B);
  if (n > m) {
    n = m;
  }
  for (int j = 0; j < p; ++j) {
    for (int i = 0; i < m; ++i) {
      sfloat* Cij = slap_GetElement(C, i, j);
      *Cij *= beta;
      for (int k = 0; k <= j; ++k) {
        sfloat Uik = *slap_GetElementConst(U, i, k);
        sfloat Bkj = *slap_GetElementConst(B, k, j);
        *Cij += alpha * Uik * Bkj;
      }
    }
  }
  return SLAP_NO_ERROR;
}

bool slap_CheckUpperTri(const Matrix A) {
  SLAP_ASSERT_VALID(A, false, "Can't check UpperTri: A matrix is invalid");
  bool is_triu = true;
  int n_rows = slap_NumRows(A);
  int n_cols = slap_NumCols(A);
  if (n_cols > n_rows) {
    n_cols = n_rows;
  }
  for (int j = 0; j < n_cols; ++j) {
    for (int i = j + 1; i < n_rows; ++i) {
      sfloat val = *slap_GetElementConst(A, i, j);
      if (fabs(val) > 0) {
        is_triu = false;
        break;
      }
    }
    if (!is_triu) { break; }
  }
  return is_triu;
}

bool slap_CheckLowerTri(const Matrix A) {
  SLAP_ASSERT_VALID(A, false, "Can't check LowerTri: A matrix is invalid");
  bool is_tril = true;
  int n_rows = slap_NumRows(A);
  int n_cols = slap_NumCols(A);
  if (n_rows > n_cols) {
    n_rows = n_cols;
  }
  for (int j = 0; j < n_cols; ++j) {
    for (int i = 0; i < j; ++i) {
      sfloat val = *slap_GetElementConst(A, i, j);
      if (fabs(val) > 0) {
        is_tril = false;
        break;
      }
    }
    if (!is_tril) { break; }
  }
  return is_tril;
}

enum slap_ErrorCode slap_MakeUpperTri(Matrix A) {
  SLAP_ASSERT_VALID(A, SLAP_INVALID_MATRIX, "Error in MakeUpperTri: Matrix Invalid");
  int n_rows = slap_NumRows(A);
  int n_cols = slap_NumCols(A);
  if (n_cols > n_rows) {
    n_cols = n_rows;
  }
  for (int j = 0; j < n_cols; ++j) {
    for (int i = j + 1; i < n_rows; ++i) {
      slap_SetElement(A, i, j, 0);
    }
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_MakeLowerTri(Matrix A) {
  SLAP_ASSERT_VALID(A, SLAP_INVALID_MATRIX, "Error in MakeLowerTri: Matrix Invalid");
  int n_rows = slap_NumRows(A);
  int n_cols = slap_NumCols(A);
  if (n_rows > n_cols) {
    n_rows = n_cols;
  }
  for (int j = 0; j < n_cols; ++j) {
    for (int i = 0; i < j; ++i) {
      slap_SetElement(A, i, j, 0);
    }
  }
  return SLAP_NO_ERROR;
}
