//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "copy_matrix.h"

#include <memory.h>

#include "matrix_checks.h"


enum slap_ErrorCode slap_MatrixCopy(Matrix dest, const Matrix src) {
  SLAP_CHECK_MATRIX(dest);
  SLAP_CHECK_MATRIX(src);
  if ((dest.rows != src.rows) || (dest.cols != src.cols)) {
    char msg[60];
    sprintf(msg, "Can't copy from matrix of size (%d,%d) to size (%d,%d)",
            slap_NumRows(src), slap_NumCols(src), slap_NumRows(dest), slap_NumCols(dest));
    return SLAP_THROW_ERROR(SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS, msg);
  }
  memcpy(dest.data, src.data, slap_NumElements(dest) * sizeof(double));
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_MatrixCopyTranspose(Matrix dest, const Matrix src) {
  SLAP_CHECK_MATRIX(dest);
  SLAP_CHECK_MATRIX(src);
  if ((slap_NumRows(dest) != slap_NumCols((src))) ||
      (slap_NumCols(dest) != slap_NumRows(src))) {
    char msg[80];
    sprintf(msg,
            "Matrix sizes are not transposes of each other. Got (%d,%d) and (%d,%d).\n",
            slap_NumRows(src), slap_NumCols(src), slap_NumRows(dest), slap_NumCols(dest));
    return SLAP_THROW_ERROR(SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS, msg);
  }

  for (int i = 0; i < slap_NumRows(dest); ++i) {
    for (int j = 0; j < slap_NumCols(dest); ++j) {
      int dest_index = slap_GetLinearIndex(dest, i, j);
      int src_index = slap_GetLinearIndex(src, j, i);
      dest.data[dest_index] = src.data[src_index];
    }
  }
  return SLAP_NO_ERROR;
}

enum slap_ErrorCode slap_MatrixCopyFromArray(Matrix mat, const double* data) {
  SLAP_CHECK_MATRIX(mat);
  if (!data) {
    return SLAP_THROW_ERROR(SLAP_BAD_POINTER, "Can't copy from raw array, pointer is NULL");
  }
  int len = slap_NumElements(mat);
  for (int i = 0; i < len; ++i) {
    mat.data[i] = data[i];
  }
  return SLAP_NO_ERROR;
}

