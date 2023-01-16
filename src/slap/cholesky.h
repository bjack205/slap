/**
 * @file cholesky.h
 * @author Brian Jackson (bjack205@gmail.com)
 * @brief Methods for solving systems of equations using a Cholesky dcomposition
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @addtogroup LinearAlgebra
 * @{
 */

#pragma once

#include "matrix.h"

/**
 * @brief Perform a Cholesky decomposition
 *
 * Performs a Cholesky decomposition on the square matrix @p A, storing the result in the
 * lower triangular portion of @p A.
 *
 * **Header File:** `slap/linalg.h`
 * @param  A a square symmetric matrix
 * @return slap error code. There is a dedicated code SLAP_CHOLESKY_FAIL if the factorization
 * fails due to a negative value on the diagonal (matrix isn't positive definite).
 */
enum slap_ErrorCode slap_Cholesky(Matrix A);

/**
 * @brief Solve a linear system of equation for a lower triangular matrix
 *
 * Uses backsubstitution to solve a system of equations of the following form:
 * \f[
 *  L x = b
 * \f]
 * for a lower-triangular matrix \f$ L \f$, or
 * \f[
 *  L^T x = b
 * \f]
 * if @p istransposed is true.
 *
 *
 * **Header File:** `slap/linalg.h`
 * @param[in]          L A lower-triangular matrix
 * @param[inout]       b The right-hand-side vector. Stores the solution upon completion.
 * @return slap error code
 */
enum slap_ErrorCode slap_LowerTriBackSub(Matrix L, Matrix b);

/**
 * @brief Solve a linear system of equation with a precomputed Cholesky decomposition.
 *
 * A x = b
 * L * L' x = b
 * L * y = b
 * => y = L \ b
 * L' x = y
 * => x =  L' \ y
 *
 * **Header File:** `slap/linalg.h`
 * @param[in]    A A square matrix whose Cholesky decomposition is stored in the lower
 *               triangular portion of the matrix
 * @param[inout] b The right-hand-side vector. Stores the solution upon completion of the
 *               function.
 * @return slap error code
 */
enum slap_ErrorCode slap_CholeskySolve(Matrix A, Matrix b);
