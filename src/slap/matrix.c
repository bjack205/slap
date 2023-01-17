#include "matrix.h"

Matrix slap_MatrixFromArray(int rows, int cols, double* data) {
  Matrix mat = {rows, cols, 1, rows, data, slap_DENSE};
  return mat;
}

void slap_Linear2Cart(Matrix mat, int k, int* row, int* col) {
  int rows = slap_NumRows(mat);
  *row = k % rows;
  *col = k / rows;
}

Matrix slap_Flatten(const Matrix mat) {
  SLAP_ASSERT_VALID(mat, slap_NullMatrix(), "Flatten: invalid matrix");
  SLAP_ASSERT_DENSE(mat, slap_NullMatrix(), "Flatten: input matrix must be dense");
  int size = slap_NumElements(mat);
  Matrix vec = {
      .rows = size,
      .cols = 1,
      .sx = mat.sx,
      .sy = mat.sy,
      .data = mat.data,
      .mattype = mat.mattype,
  };
  return vec;
}

Matrix slap_Transpose(Matrix A) {
  enum slap_MatrixType transposed_type;
  if (A.mattype == slap_DENSE) {
    transposed_type = slap_TRANSPOSED;
  } else if (A.mattype == slap_TRANSPOSED) {
    transposed_type = slap_DENSE;
  } else {
    transposed_type = A.mattype;
  }
  Matrix new_mat = {
      .rows = A.rows,
      .cols = A.cols,
      .sx = A.sx,
      .sy = A.sy,
      .data = A.data,
      .mattype = transposed_type,
  };
  return new_mat;
}

Matrix slap_Reshape(Matrix mat, int rows, int cols) {
  SLAP_ASSERT_VALID(mat, slap_NullMatrix(), "Reshape: invalid matrix");
  SLAP_ASSERT_DENSE(mat, slap_NullMatrix(), "Reshape: input matrix must be dense");
  SLAP_ASSERT(rows >= 0, SLAP_INVALID_DIMENSION, slap_NullMatrix(),
              "Reshape: number of rows must be positive, got %d", rows);
  SLAP_ASSERT(cols >= 0, SLAP_INVALID_DIMENSION, slap_NullMatrix(),
              "Reshape: number of columns must be positive, got %d", cols);
  Matrix new_mat = {
      .rows = rows,
      .cols = cols,
      .data = mat.data,
      .sx = 1,
      .sy = rows,
      .mattype = mat.mattype,
  };
  new_mat.rows = rows;
  new_mat.cols = cols;
  return new_mat;
}
