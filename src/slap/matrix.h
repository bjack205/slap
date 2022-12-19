/**
 * @file matrix.h
 * @author Brian Jackson (bjack205@gmail.com)
 * @brief Matrix type and basic operations
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @addtogroup LinearAlgebra
 * @{
 */
#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include "errors.h"

enum slap_MatrixType {
  slap_DENSE,
  slap_TRANSPOSED,
  //  slap_DIAGONAL
};

/**
 * @brief Represents a matrix of double-precision data
 *
 * Simple wrapper around an arbitrary pointer to the underlying data.
 * The data is assumed to be stored in a contiguous block of memory.
 * The data is interpreted column-wise, such that `data[1]` is element `[1,0]` of the
 * matrix.
 *
 * ## Initialization
 * A Matrix can be initialized a few ways. The easiest is via `NewMatrix`:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Matrix mat = slap_NewMatrix(rows, cols);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * which allocates a new block of memory on the heap. It must be followed by a call to
 * FreeMatrix().
 *
 * If the data for the matrix is already stored in an array, the default brace initializer
 * can be used:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * double data[6] = {1,2,3,4,5,6};
 * Matrix mat = {2, 3, data};
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ## Methods
 * The following methods are defined for the Matrix type:
 *
 * ### Initialization and deconstruction
 * - slap_NewMatrix()
 * - FreeMatrix()
 * - MatrixSetConst()
 * - MatrixScaleByConst()
 *
 * ### Indexing operations
 * - MatrixNumElements()
 * - MatrixGetLinearIndex()
 * - MatrixGetElement()
 * - MatrixGetElementTranspose()
 * - MatrixSetElement()
 *
 * ### Copying
 * - MatrixCopy()
 * - MatrixCopyTranspose()
 *
 * ### Reshaping
 * - MatrixFlatten()
 * - MatrixFlattenToRow()
 *
 * ### Utilities
 * - PrintMatrix()
 * - PrintRowVector()
 * - MatrixNormedDifference()
 */
typedef struct {
  uint16_t rows;
  uint16_t cols;
  uint16_t sx;
  uint16_t sy;
  double* data;
  enum slap_MatrixType mattype;
} Matrix;

static inline Matrix slap_NullMatrix(void) {
  // NOTE: Can't use named initializer here because it's inlined
  // (so causes issues for C++)
  Matrix mat = {
      0, 0, 0, 0, NULL, slap_DENSE,
  };
  return mat;
}

static inline bool slap_IsTransposed(Matrix A) { return A.mattype == slap_TRANSPOSED; }

static inline bool slap_IsEmpty(Matrix mat) { return mat.rows <= 0 || mat.cols <= 0; }

static inline bool slap_IsSquare(Matrix mat) { return mat.rows == mat.cols; }

static inline bool slap_IsDense(Matrix mat) { return mat.sx == 1 && mat.sy == mat.rows; }

static inline uint16_t slap_MinDim(Matrix mat) {
  return mat.rows <= mat.cols ? mat.rows : mat.cols;
}

static inline int slap_NumRows(Matrix mat) {
  return slap_IsTransposed(mat) ? mat.cols : mat.rows;
}

static inline int slap_NumCols(Matrix mat) {
  return slap_IsTransposed(mat) ? mat.rows : mat.cols;
}

/**
 * @brief Wraps existing data in a Matrix class
 *
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @param data Data for the matrix. Must not be NULL, and should have at least
 *             rows * cols elements.
 * @return A new matrix
 */
Matrix slap_MatrixFromArray(int rows, int cols, double* data);


/**
 * @brief Get the number of elements in a matrix, i.e. `m * n`.
 *
 * @param mat Any matrix
 * @return Number of elements in the matrix
 */
static inline int slap_NumElements(const Matrix mat) { return mat.rows * mat.cols; }

/**
 * @brief Get the linear index for a given row and column in the matrix
 *
 * Converts a cartesian index of row and column into a linear index for accessing
 * an element of the underlying data.
 *
 * @param mat Matrix with nonzero size and initialized data
 * @param row Row index
 * @param col Column index
 * @return Linear index corresponding to `row` and `col`.
           Returns -1 for a bad input.
 */
static inline int slap_GetLinearIndex(const Matrix mat, int row, int col) {
  return (mat.mattype == slap_TRANSPOSED) ? col + mat.rows * row : row + mat.rows * col;
}

/**
 * @brief Check if the row and column index is in the bounds of the matrix
 *
 * @param mat Matrix to be indexed
 * @param row Row index
 * @param col Column index
 * @return true if the row and column index is in bounds for the matrix
 */
static inline bool slap_CheckInbounds(Matrix mat, int row, int col) {
  return (row >= 0 && row < mat.rows) && (col >= 0 && col < mat.cols);
}

/**
 * @brief Get a pointer to matrix element given row, column indices
 *
 * Note that this method does NOT perform any bounds checking so can be used unsafely!
 * Passing an index that is out of bounds is undefined behavior.
 *
 * @param mat Matrix of nonzero size
 * @param row Row index
 * @param col Column index
 * @return A pointer to the element of the matrix. NULL for invalid input.
 */
static inline double* slap_GetElement(Matrix mat, int row, int col) {
  return mat.data + slap_GetLinearIndex(mat, row, col);
}

/**
 * @brief Get a const pointer to matrix element given row, column indices
 *
 * @param mat Matrix of nonzero size
 * @param row Row index
 * @param col Column index
 * @return A pointer to the element of the matrix. NULL for invalid input.
 */
static inline const double* slap_GetElementConst(const Matrix mat, int row, int col) {
  return mat.data + slap_GetLinearIndex(mat, row, col);
}

/**
 * @brief The a matrix element to a given value
 *
 * @param mat Matrix with nonzero size and initialized data
 * @param row Row index
 * @param col Column index
 * @param val Value to which the element should be set
 * @return    0 if successful
 */
static inline void slap_SetElement(Matrix mat, int row, int col, double val) {
  mat.data[slap_GetLinearIndex(mat, row, col)] = val;
}

/**
 * @brief Sets all of the elements in a matrix to a single value
 *
 * @param mat Matrix to be modified
 * @param val Value to which each element will be set
 * @return 0 if successful
 */
enum slap_ErrorCode slap_SetConst(Matrix mat, double val);

/**
 * @brief Copy a matrix to another matrix
 *
 * @param dest a matrix of size (m,n)
 * @param src a matrix of size (n,m)
 * @return 0 if successful
 */
enum slap_ErrorCode slap_MatrixCopy(Matrix dest, Matrix src);

/**
 * @brief Copy a matrix to another matrix, transposed
 *
 * @param dest a matrix of size (m,n)
 * @param src a matrix of size (n,m)
 * @return 0 if successful
 */
enum slap_ErrorCode slap_MatrixCopyTranspose(Matrix dest, Matrix src);

/**
 * @brief Copy the data from an array into the matrix, columnwise.
 *
 * @param mat  Matrix with nonzero size
 * @param data Data to be copied into the array. Must have length of at least mat.rows *
 * mat.cols.
 * @return 0 if successful
 */
enum slap_ErrorCode slap_MatrixCopyFromArray(Matrix mat, const double* data);

/**
 * @brief Set the diagonal elements of the matrix to val, and the rest to zeros.
 *
 * @param mat Square matrix
 * @param val Value for the diagonal elements
 * @return
 */
enum slap_ErrorCode slap_SetIdentity(Matrix mat, double val);

/**
 * @brief Scale a matrix by a constant factor
 *
 * @param mat Fully initialized matrix of non-zero size. Values will be modified.
 * @param alpha scalar by which to multiply the matrix
 * @return 0 if successsful
 */
enum slap_ErrorCode slap_ScaleByConst(Matrix mat, double alpha);

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

/**
 * @brief Return the normed difference between 2 matrices of the same size
 *
 * Returns \f$ \sqrt{\sum_{i=0}^{m-1} \sum_{j=0}^{n-1} (A_{ij} - B_{ij})^2 } \f$
 *
 * @param A A matrix of dimension (m,n)
 * @param B A matrix of dimension (m,n)
 * @return
 */
double slap_MatrixNormedDifference(Matrix A, Matrix B);

/**
 * @brief Flatten a 2D matrix to a column vector
 *
 * Changes the row and column data so that the matrix is now a column vector. The
 * underlying data is unchanged.
 *
 * @param mat Matrix to be flattened.
 * @return 0 if successful
 */
Matrix slap_Flatten(Matrix mat);

/**
 * @brief Transpose a 2D matrix
 *
 * This operation doesn't change the data, just it's interpretation.
 *
 * @param mat The matrix to transpose
 * @return A transposed Matrix object
 */
Matrix slap_Transpose(Matrix mat);

/**
 * @brief Set the dimensions of the matrix
 *
 * Note that this does not change the underlying data, only it's interpretation.
 *
 * @param mat  Matrix
 * @param rows New number of rows
 * @param cols New number of columns
 * @return 0 if successful
 */
Matrix slap_Reshape(Matrix mat, int rows, int cols);

/**@}*/
