/**
 * @file function_mapping.h
 * @author Brian Jackson (bjack205@gmail.com)
 * @brief Method for applying functions element-wise
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @addtogroup Advanced
 * @{
 */

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
