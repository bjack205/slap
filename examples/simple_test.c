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
  (void)n_rows;
  (void)n_cols;
  (void)n_el;

  // Get a pointer to an element
  double *pa = slap_GetElement(A, 0, 0);
  double a = *slap_GetElement(A, 0, 1);
  (void)pa;
  (void)a;
  printf("A[0,0] = %0.3g\n", *pa);
  printf("A[0,1] = %0.3g\n", a);

  // Set an element via pointer
  *pa = -20;
  printf("A[0,0] = %0.3g (after set)\n", *slap_GetElement(A, 0, 0));

  // Set an element directly
  slap_SetElement(A, 1, 2, 25.5);
  printf("A[1,2] = %0.3g (after set)\n", *slap_GetElement(A, 1, 2));
  
  printf("\n~~~~~~~~~~~~~~~ UNARY OPS ~~~~~~~~~~~~~~\n");

  // Printing
  printf("\nA:\n");
  slap_PrintMatrix(A);

  return 0;
}
