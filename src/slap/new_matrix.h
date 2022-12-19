//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

/**
 * @brief Allocate a new matrix on the heap
 *
 * Data will not be initialized. Wrapper around a call to `malloc`.
 * Must be followed by a call to `FreeMatrix`.
 *
 * @param rows number of rows in the matrix
 * @param cols number of columns in the matrix
 * @return A new matrix
 */
Matrix slap_NewMatrix(int rows, int cols);

/**
 * @brief Allocate a new matrix on the heap, initialized with zeros
 *
 * Data will not be initialized. Wrapper around a call to `malloc`.
 * Must be followed by a call to `FreeMatrix`.
 *
 * @param rows number of rows in the matrix
 * @param cols number of columns in the matrix
 * @return A new matrix
 */
Matrix slap_NewMatrixZeros(int rows, int cols);

/**
 * @brief Free the data for a matrix
 *
 * Note this does NOT attempt to free the matrix object itself, only the data
 * it wraps.
 *
 * @param mat
 * @post [mat.data](Matrix.data) will be `NULL`.
 * @return 0 if successful
 */
int slap_FreeMatrix(Matrix mat);
