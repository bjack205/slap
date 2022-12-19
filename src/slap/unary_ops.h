//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

/**
 * @brief Sets all of the elements in a matrix to a single value
 *
 * @param mat Matrix to be modified
 * @param val Value to which each element will be set
 * @return 0 if successful
 */
enum slap_ErrorCode slap_SetConst(Matrix mat, double val);

/**
 * @brief Scale a matrix by a constant factor
 *
 * @param mat Fully initialized matrix of non-zero size. Values will be modified.
 * @param alpha scalar by which to multiply the matrix
 * @return 0 if successsful
 */
enum slap_ErrorCode slap_ScaleByConst(Matrix mat, double alpha);

/**
 * @brief Set the diagonal elements of the matrix to val, and the rest to zeros.
 *
 * @param mat Square matrix
 * @param val Value for the diagonal elements
 * @return
 */
enum slap_ErrorCode slap_SetIdentity(Matrix mat, double val);

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
