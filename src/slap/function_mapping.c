//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "function_mapping.h"

#include "iterator.h"
#include "matrix_checks.h"

enum slap_ErrorCode slap_Map(Matrix mat, double (*function)(double)) {
 SLAP_CHECK_MATRIX(mat);
  for (MatrixIterator it = slap_Iterator(mat); !slap_IsFinished(&it); slap_Step(&it)) {
    double *value = mat.data + it.index;
   *value = function(*value);
  }
  return SLAP_NO_ERROR;
}
