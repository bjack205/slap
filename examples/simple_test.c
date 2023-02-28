//
// Created by Brian Jackson on 2/27/23.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#include <stdlib.h>

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

  // Set the matrix to a constant
  const double val = 1.2;
  slap_SetConst(A, val);
  printf("\nA: (set const)\n");
  slap_PrintMatrix(A);

  // Scale by constant
  slap_ScaleByConst(A, -1);
  printf("\nA: (Scale by const)\n");
  slap_PrintMatrix(A);

  // Set Identity
  slap_SetIdentity(A, 2.1);
  printf("\nA: (Set to identity)\n");
  slap_PrintMatrix(A);

  // Set Diagonal
  double diag[3] = {1,2,3};
  slap_SetDiagonal(A, diag, 3);
  printf("\nA: (Set Diagonal)\n");
  slap_PrintMatrix(A);

  // Set first n elements of diagonal
  diag[0] = 10;
  diag[1] = 11;
  slap_SetDiagonal(A, diag, 2);
  printf("\nA: (Set Partial Diagonal)\n");
  slap_PrintMatrix(A);

//  // Set Range
//  slap_SetRange(A, 1, slap_NumElements(A));
//  printf("\nA: (Set Range)\n");
//  slap_PrintMatrix(A);

//  slap_SetRange(A, 0, 1);
//  printf("\nA: (Set Range 0 to 1)\n");
//  slap_PrintMatrix(A);

  /////////////////////////////////////////////
  // Transformations
  /////////////////////////////////////////////

  printf("\n~~~~~~~~~~~~ TRANSFORMATIONS ~~~~~~~~~~~\n");

  // Transpose
  Matrix At = slap_Transpose(A);
  printf("\nA transpose:\n");
  slap_PrintMatrix(At);
  bool tA = slap_IsTransposed(At);
  printf("At is transposed? %d\n", tA);

  // Flatten
  Matrix vec_a = slap_Flatten(A);
  printf("\nA Flatten\n");
  slap_PrintMatrix(vec_a);

  // Reshape
  Matrix A2 = slap_Reshape(A, 2, 6);
  printf("\nA2\n");
  slap_PrintMatrix(A2);

  // Modify reshape (note that it changes the original)
  slap_SetElement(A2, 0, 1, 100);
  printf("\nA (after edit via reshape)\n");
  slap_PrintMatrix(A);

  // Reshape to smaller
  // note this is 1st 4 elements, not top left corner
  Matrix A_resize = slap_Reshape(A, 2, 2);
  printf("\nA resize\n");
  slap_PrintMatrix(A_resize);

  /////////////////////////////////////////////
  // Copying
  /////////////////////////////////////////////

  printf("\n~~~~~~~~~~~~~~~ COPYING ~~~~~~~~~~~~~~~\n");

  // Matrix with heap-allocated memory
  double *data_B = (double*)malloc(n_el * sizeof(double));
  Matrix B = slap_MatrixFromArray(4, 3, data_B);

  // Copy from transposed array
  slap_MatrixCopy(B, At);

  printf("\nCopy from A to B:\n");
  printf("A:\n");
  slap_PrintMatrix(A);
  printf("B:\n");
  slap_PrintMatrix(B);

  // Copy from array
  double data_C[4] = {-1,2,-3,4};
  slap_MatrixCopyFromArray(A_resize, data_C);  // note we're copying to a reshaped version of A

  printf("\nA (after array copy):\n");
  slap_PrintMatrix(A);

  /////////////////////////////////////////////
  // Sub-Arrays
  /////////////////////////////////////////////

  printf("\n~~~~~~~~~~~~~~ SUB-ARRAYS ~~~~~~~~~~~~~~\n");

  // Get view of top-left 2x2 corner
  Matrix A_sub = slap_CreateSubMatrix(A, 0, 0, 2, 2);
  printf("\nTop-left corner of A\n");
  slap_PrintMatrix(A_sub);
  printf("A is Dense?     %d\n", slap_IsDense(A));
  printf("A sub is Dense? %d\n", slap_IsDense(A_sub));

  // Copy to Sub-matrix
  data_C[3] = -50;
  slap_MatrixCopyFromArray(A_sub, data_C);
  printf("\nA (after copying to sub-matrix)\n");
  slap_PrintMatrix(A);

  // Get middle elements
  A_sub = slap_CreateSubMatrix(A, 1, 1, 1, 2);
  printf("\nMiddle of A\n");
  slap_PrintMatrix(A_sub);

  /////////////////////////////////////////////
  // Vector Operations
  /////////////////////////////////////////////

  printf("\n~~~~~~~~~~~~~~ VECTOR OPS ~~~~~~~~~~~~~~\n");

  // Create Matrices (vectors) on the heap
  // Note the calls to slap_FreeMatrix at the bottom of this function
  Matrix x = slap_NewMatrix(3, 1);
  Matrix y = slap_NewMatrix(3, 1);
  Matrix z = slap_NewMatrixZeros(3, 1);
  (void)x;
  (void)y;
  (void)z;

  // Set some values
//  slap_SetRange(x, 1, 3);
  for (int i = 0; i < 3; ++i) {
    x.data[i] = i + 1;
  }
  slap_SetConst(y, 1.5);

  // Inner product
  double dot_xy = slap_InnerProduct(x, y);
  printf("Inner product = %0.3g\n", dot_xy);

  // Cross product
  slap_CrossProduct(z, x, y);
  printf("Cross product: ");
  slap_PrintMatrix(slap_Transpose(z));

  // Norms (only for dense)
  printf("Two Norm Squared: %0.2g\n", slap_NormTwoSquared(z));
  printf("Two Norm:         %0.2g\n", slap_NormTwo(z));
  printf("One Norm:         %0.2g\n", slap_NormOne(z));
  printf("Inf Norm:         %0.2g\n", slap_NormInf(z));

  // Max/Min
  printf("Max: %0.2g\n", slap_Max(z));
  printf("Min: %0.2g\n", slap_Min(z));

  // Argmax/Argmin
  double z_max, z_min;
  MatrixIterator it_max = slap_ArgMax(z, &z_max);
  MatrixIterator it_min = slap_ArgMin(z, &z_min);
  printf("ArgMax: %0.2g at linear index, %d, Cartesian index (%d,%d)\n", z_max,
         it_max.k, it_max.i, it_max.j);
  printf("ArgMin: %0.2g at linear index, %d, Cartesian index (%d,%d)\n", z_max,
         it_min.k, it_min.i, it_min.j);

  // Outer Product
  Matrix Z = slap_NewMatrix(3, 3);
  slap_OuterProduct(Z, x, y);
  printf("\nOuter Product:\n");
  slap_PrintMatrix(Z);

  return 0;
}
