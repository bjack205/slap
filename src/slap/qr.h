//
// Created by Brian Jackson on 1/22/23.
// Copyright (c) 2023 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

/**
 * @brief Performs QR decomposition
 *
 * Calculates the QR decomposition using Householder reflections.
 * The R factor is stored in the upper triangular portion of A,
 * while the reflection vectors are stored below the diagonal, which
 * can be used to recover the Q matrix.
 *
 * @param A A square or skinny matrix
 * @param[out] betas Stores scaling factors needed to recover Q. Must have
 *                   the same number of rows as A.
 * @param[in] temp A temporary vector with the same number of rows as A.
 */
enum slap_ErrorCode slap_QR(Matrix A, Matrix betas, Matrix temp);

/**
 * @brief Computes the Q matrix from a previously-computed QR decomposition
 * @param[out] A A square matrix with the same number of rows as R.
 * @param[in] R A square or skinny matrix containing the results from a QR decomposition.
 * @param[in] betas A vector of scaling factors needed to recover the Q matrix.
 * @param Q_work A temporary matrix of the same size as Q for intermediate calculations
 */
enum slap_ErrorCode slap_ComputeQ(Matrix Q, const Matrix R, const Matrix betas,
                                  Matrix Q_work);

/**
 * @brief Calculates \f$Q^T b\f$ where $Q$ is the orthogonal matrix from a QR decomposition
 *
 * This method is useful for solving linear systems with the QR decomposition, where the
 * right side needs to be multiplied by \f$Q^T\f$.
 *
 * The result is stored in b.
 *
 * @param[in] R
 * @param b
 */
enum slap_ErrorCode slap_Qtb(const Matrix R, Matrix b);
