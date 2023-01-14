//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

/**
 * @brief Return the normed difference between 2 matrices of the same size
 *
 * Returns \f$ \sqrt{\sum_{i=0}^{m-1} \sum_{j=0}^{n-1} (A_{ij} - B_{ij})^2 } \f$
 *
 * @param A A matrix of dimension (m,n)
 * @param B A matrix of dimension (m,n)
 * @return NAN if input is invalid, normed difference otherwise
 */
double slap_MatrixNormedDifference(Matrix A, Matrix B);

enum slap_ErrorCode slap_MatAdd(Matrix C, Matrix A, Matrix B, double alpha);
