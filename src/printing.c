#include "printing.h"

#include <stdio.h>

int slap_PrintMatrix(const Matrix mat) {
  for (int row = 0; row < mat.rows; ++row) {
    for (int col = 0; col < mat.cols; ++col) {
      printf("% 6.*g ", PRECISION, *slap_GetElementConst(mat, row, col));
    }
    printf("\n");
  }
  return 0;
}

int slap_PrintRowVector(Matrix mat) {
  printf("[ ");
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    printf("% 6.*g ", PRECISION, mat.data[i]);
  }
  printf("]\n");
  return 0;
}
