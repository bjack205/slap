//
// Created by Brian Jackson on 12/19/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "matmul.h"
enum slap_ErrorCode slap_MatMulAdd(Matrix C, Matrix A, Matrix B, double alpha,
                                double beta) {
  int n = slap_NumRows(A);
  int m = slap_NumCols(A);
  int p = slap_NumCols(B);
  if (slap_NumRows(B) != m || slap_NumRows(C) != n || slap_NumCols(C) != p) {
    char msg[100];
    sprintf(msg, "Cannot multiply matrices. C = (%d,%d,%d), A = (%d,%d,%d), B = (%d,%d,%d)",
            slap_NumRows(C), slap_NumCols(C), slap_IsTransposed(C), slap_NumRows(A),
            slap_NumCols(A), slap_IsTransposed(A), slap_NumRows(B), slap_NumCols(B),
            slap_IsTransposed(B));
    return SLAP_THROW_ERROR(SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS, msg);
  }
  for (int i = 0; i < n; ++i) {    // rows of output
    for (int j = 0; j < p; ++j) {  // Columns of output
      double* Cij = slap_GetElement(C, i, j);
      *Cij *= beta;
      for (int k = 0; k < m; ++k) {  // columns of A, rows of B
        double Aik  = *slap_GetElementConst(A, i, k);
        double Bkj  = *slap_GetElementConst(B, k, j);
        *Cij += alpha * Aik * Bkj;
      }
    }
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_MatMulAB(Matrix C, Matrix A, Matrix B) {
  // C is n x p
  // A is n x m
  // B is m x p
  int n = A.rows;
  int m = A.cols;
  int p = B.cols;
  double Aik;
  double Bkj;
  double Cij;
  int ij;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      ij = i + j * n;
      Cij = 0;
      for (int k = 0; k < m; ++k) {  // columns of A, rows of B
        Aik = A.data[i + n * k];
        Bkj = B.data[k + m * j];
        Cij += Aik * Bkj;
      }
      C.data[ij] = Cij;
    }
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_MatMulAtB(Matrix C, Matrix A, Matrix B) {
  // C is n x p
  // A is m x n
  // B is m x p
  int n = A.cols;
  int m = A.rows;
  int p = B.cols;
  int ij;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      ij = i + n * j;
      double Cij = 0;
      for (int k = 0; k < m; ++k) {
        double Aki = A.data[k + i * m];
        double Bkj = B.data[k + j * m];
        Cij += Aki * Bkj;
      }
      C.data[ij] = Cij;
    }
  }
  return SLAP_NO_ERROR;
}
