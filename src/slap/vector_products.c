//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "vector_products.h"

//double slap_QuadraticForm(const Matrix x, const Matrix A, const Matrix y) {
//  if ((y.rows != A.rows) || (x.rows != A.cols) || (x.cols != 1) || (y.cols != 1)) {
//    return NAN;
//  }
//  double out = 0.0;
//  for (int i = 0; i < x.rows; ++i) {
//    for (int j = 0; j < y.rows; ++j) {
//      double xi = x.data[i];
//      double yj = y.data[j];
//      double Aij = *slap_MatrixGetElementConst(&A, i, j);
//      out += xi * Aij * yj;
//    }
//  }
//  return out;
//}
