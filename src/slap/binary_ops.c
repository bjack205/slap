//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "binary_ops.h"

#include <math.h>

double slap_MatrixNormedDifference(const Matrix A, const Matrix B) {
  if (!A.data || !B.data) {
    //    SLAP_ERRNO = SLAP_BAD_MATRIX_DATA_POINTER;
    return INFINITY;
  }
  if ((A.rows != B.rows) || (A.cols != B.cols)) {
    fprintf(stderr, "Can't compare matrices of different sizes. Got (%d,%d) and (%d,%d)\n",
            A.rows, A.cols, B.rows, B.cols);
    return INFINITY;
  }

  double diff = 0;
  for (int i = 0; i < slap_NumElements(A); ++i) {
    double d = A.data[i] - B.data[i];
    diff += d * d;
  }
  return sqrt(diff);
}

