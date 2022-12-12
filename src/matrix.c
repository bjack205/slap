#include "matrix.h"

#ifndef PRECISION
#define PRECISION 5
#endif

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_checks.h"

Matrix slap_MatrixFromArray(int rows, int cols, double* data) {
  Matrix mat = {rows, cols, 1, rows, data, slap_DENSE};
  return mat;
}

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

int slap_FreeMatrix(Matrix mat) {
  if (mat.data) {
    free(mat.data);
    mat.data = NULL;
    return SLAP_NO_ERROR;
  }
  return SLAP_BAD_MATRIX_DATA_POINTER;
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
  SLAP_ASSERT_SQUARE(mat, "Cannot set matrix to identity");
  slap_SetConst(mat, 0.0);
  for (int i = 0; i < mat.rows; ++i) {
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
      .mattype = slap_DENSE,
  };
  return vec;
}

// Matrix slap_MatrixFlattenToRow(Matrix mat) {
//   if (!mat) {
//     return -1;
//   }
//   int size = slap_NumElements(mat);
//   mat->rows = 1;
//   mat->cols = size;
//   return 0;
// }

int slap_PrintMatrix(const Matrix mat) {
  for (int row = 0; row < mat.rows; ++row) {
    for (int col = 0; col < mat.cols; ++col) {
      printf("% 6.*g ", PRECISION, *slap_GetElementConst(mat, row, col));
    }
    printf("\n");
  }
  return 0;
}

int slap_PrintRowVector(Matrix mat) {
  printf("[ ");
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    printf("% 6.*g ", PRECISION, mat.data[i]);
  }
  printf("]\n");
  return 0;
}

int slap_SetMatrixSize(Matrix* mat, int rows, int cols) {
  if (!mat) {
    return -1;
  }
  if (rows < 1 || cols < 1) {
    printf("ERROR: rows and columns must be positive integers.\n");
    return -1;
  }
  mat->rows = rows;
  mat->cols = cols;
  return 0;
}

int slap_MatrixSetDiagonal(Matrix* mat, const double* diag) {
  // TODO: check size (cols >= rows)
  for (int i = 0; i < mat->rows; ++i) {
    slap_SetElement(*mat, i, i, diag[i]);
  }
  return 0;
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
  Matrix result = {
      .rows = A.rows,
      .cols = A.cols,
      .sx = A.sx,
      .sy = A.sy,
      .data = A.data,
      .mattype = transposed_type,
  };
  return result;
}
