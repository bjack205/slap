//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"


/**
 * @brief Copy a matrix to another matrix
 *
 * @param dest a matrix of size (m,n)
 * @param src a matrix of size (n,m)
 * @return slap error code
 */
enum slap_ErrorCode slap_MatrixCopy(Matrix dest, Matrix src);

/**
 * @brief Copy a matrix to another matrix, transposed
 *
 * @param dest a matrix of size (m,n)
 * @param src a matrix of size (n,m)
 * @return slap error code
 */
enum slap_ErrorCode slap_MatrixCopyTranspose(Matrix dest, Matrix src);

/**
 * @brief Copy the data from an array into the matrix
 *
 * The data is always copied into the same order as the underlying memory layout, so
 * this method ignores whether the matrix is transposed or not.
 *
 * @param mat  A valid matrix
 * @param data Data to be copied into the array. Must have length of at least mat.rows * * mat.cols.
 * @return slap error code
 */
enum slap_ErrorCode slap_MatrixCopyFromArray(Matrix mat, const double* data);
