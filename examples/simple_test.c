//
// Created by Brian Jackson on 2/27/23.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#include "slap/slap.h"

int main(void) {
  double data_A[12] = {1,2,3, 4,5,6, 7,8,9, 10,11,12};
  Matrix A = slap_MatrixFromArray(3, 4, data_A);
  // Get the sizes of the matrix
  int n_rows = slap_NumRows(A);
  int n_cols = slap_NumCols(A);
  int n_el = slap_NumElements(A);

  // Get a pointer to an element
  double *pa = slap_GetElement(A, 0, 0);
  double a = *slap_GetElement(A, 0, 1);
  return 0;
}
