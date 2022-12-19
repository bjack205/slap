//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "strided_matrix.h"

Matrix slap_CreateSubMatrix(Matrix mat, int top_left_row, int top_left_col, int new_rows,
                      int new_cols) {
  Matrix new_mat = slap_NullMatrix();
  if (new_rows < 0) {
    char msg[50];  // NOLINT
    sprintf(msg, "Invalid SubMatrix with dimension (%d,%d)", new_rows, new_cols);
    (void)SLAP_THROW_ERROR(SLAP_INVALID_DIMENSION, msg);
    return new_mat;
  }
  if (new_cols < 0) {
    char msg[50];  // NOLINT
    sprintf(msg, "Invalid SubMatrix with dimension (%d,%d)", new_rows, new_cols);
    (void)SLAP_THROW_ERROR(SLAP_INVALID_DIMENSION, msg);
    return new_mat;
  }
  if (!slap_CheckInbounds(mat, top_left_row + new_rows - 1, top_left_col + new_cols - 1)) {
    char msg[100];  // NOLINT
    sprintf(msg,
            "Invalid SubMatrix. Bottom-right corner (%d,%d) outside parent matrix with "
            "size (%d,%d)",
            top_left_row + new_rows - 1, top_left_col + new_cols - 1, mat.rows, mat.cols);
    (void)SLAP_THROW_ERROR(SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS, msg);
    return new_mat;
  }
  new_mat.rows = new_rows;
  new_mat.cols = new_cols;
  new_mat.sx = mat.sx;
  new_mat.sy = mat.sy;
  int top_left_index = slap_Cart2Index(mat, top_left_row, top_left_col);
  new_mat.data = mat.data + top_left_index;
  new_mat.mattype = mat.mattype;
  return new_mat;
}
