//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

double slap_InnerProduct(Matrix x, Matrix y);

/**
 * @brief Calculate the scaled inner product \f$ y^T A x \f$
 *
 * @param x A vector of length n
 * @param A A matrix of size (n,m)
 * @param y A vector of length m
 * @return The dot product, or NAN if invalid.
 */
double slap_QuadraticForm(Matrix y, Matrix Q, Matrix x);

enum slap_ErrorCode slap_OuterProduct(Matrix C, Matrix x, Matrix y);

enum slap_ErrorCode slap_CrossProduct(Matrix z, Matrix x, Matrix y);
