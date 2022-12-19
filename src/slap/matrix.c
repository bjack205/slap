#include "matrix.h"

#include <math.h>
#include <memory.h>

#include "matrix_checks.h"

Matrix slap_MatrixFromArray(int rows, int cols, double* data) {
  Matrix mat = {rows, cols, 1, rows, data, slap_DENSE};
  return mat;
}

enum slap_ErrorCode slap_SetConst(Matrix mat, double val) {
  SLAP_CHECK_MATRIX(mat);
  int num_el = slap_NumElements(mat);
  for (int i = 0; i < num_el; ++i) {
    mat.data[i] = val;
  }
  return SLAP_NO_ERROR;
}

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

enum slap_ErrorCode slap_SetDiagonal(Matrix mat, const double* diag, int len) {
  int n = slap_MinDim(mat);
  n = n <= len ? n : len;
  for (int i = 0; i < n; ++i) {
    slap_SetElement(mat, i, i, diag[i]);
  }
  return SLAP_NO_ERROR;
}

double slap_MatrixNormedDifference(const Matrix A, const Matrix B) {
  if (!A.data || !B.data) {
    //    SLAP_ERRNO = SLAP_BAD_MATRIX_DATA_POINTER;
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

Matrix slap_Flatten(const Matrix mat) {
  int size = slap_NumElements(mat);
  Matrix vec = {
      .rows = size,
      .cols = 1,
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
  if (rows < 1 || cols < 1) {
    printf("ERROR: rows and columns must be positive integers.\n");
  }
  if (!slap_IsDense(mat)) {
    (void)SLAP_THROW_ERROR(SLAP_MATRIX_NOT_DENSE, "Reshape only supported for dense matrices");
    return slap_NullMatrix();
  }
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
