//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

/**
 * @brief Applies a function element-wise to every element in the matrix
 *
 * Applies `mat[k] = function(mat[k])` for all elements
 *
 * @param mat A valid matrix (can be dense or strided)
 * @param function A function pointer that takes and returns a double
 * @return
 */
enum slap_ErrorCode slap_Map(Matrix mat, double (*function)(double));
