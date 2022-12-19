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
