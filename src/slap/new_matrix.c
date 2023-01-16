//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "new_matrix.h"

#include <stdlib.h>

Matrix slap_NewMatrix(int rows, int cols) {
  double* data = (double*)malloc(rows * cols * sizeof(double));
  Matrix mat = {rows, cols, 1, rows, data, slap_DENSE};
  return mat;
}

Matrix slap_NewMatrixZeros(int rows, int cols) {
  double* data = (double*)calloc(rows * cols, sizeof(double));
  Matrix mat = {rows, cols, 1, rows, data, slap_DENSE};
  return mat;
}

enum slap_ErrorCode slap_FreeMatrix(Matrix mat) {
  if (mat.data) {
    free(mat.data);
    mat.data = NULL;
    return SLAP_NO_ERROR;
  }
  return SLAP_BAD_MATRIX_DATA_POINTER;
}
