#include "matrix.h"

#include <math.h>

#include "simpletest/simpletest.h"

int TestNewMatrix(void) {
  Matrix mat = slap_NewMatrix(5, 4);
  TEST(mat.rows == 5);
  TEST(mat.cols == 4);
  TEST(slap_MatrixNumElements(&mat) == 20);
  slap_FreeMatrix(&mat);
  return 1;
}

int SetConst(void) {
  Matrix mat = slap_NewMatrix(3, 4);
  slap_MatrixSetConst(&mat, 5.0);
  for (int i = 0; i < 12; ++i) {
    TEST(mat.data[i] == 5);
  }
  slap_MatrixSetConst(&mat, -4.2);
  for (int i = 0; i < 12; ++i) {
    TEST(mat.data[i] == -4.2);
  }
  slap_FreeMatrix(&mat);
  return 1;
}

int GetIndex(void) {
  Matrix mat = slap_NewMatrix(3, 4);
  for (int i = 0; i < 12; ++i) {
    mat.data[i] = i;
  }
  TEST(*slap_MatrixGetElement(&mat, 0, 0) == 0);
  TEST(*slap_MatrixGetElement(&mat, 1, 0) == 1);
  TEST(*slap_MatrixGetElement(&mat, 0, 1) == 3);
  TEST(*slap_MatrixGetElement(&mat, 2, 3) == 11);
  slap_FreeMatrix(&mat);
  return 1;
}

int TestPrintMatrix(void) {
  Matrix mat = slap_NewMatrix(3, 4);
  for (int i = 0; i < 12; ++i) {
    mat.data[i] = i;
  }
  slap_PrintMatrix(&mat);
  slap_FreeMatrix(&mat);
  return 1;
}

int CopyMatrix(void) {
  Matrix src = slap_NewMatrix(10, 12);
  for (int i = 0; i < slap_MatrixNumElements(&src); ++i) {
    src.data[i] = i * i - sqrt(i * 2.1);
  }
  Matrix dest = slap_NewMatrix(10, 12);
  slap_MatrixCopy(&dest, &src);
  for (int i = 0; i < slap_MatrixNumElements(&src); ++i) {
    TEST(dest.data[i] == i * i - sqrt(i * 2.1));
  }
  slap_FreeMatrix(&src);
  slap_FreeMatrix(&dest);
  return 1;
}

int CopyTranspose(void) {
  Matrix src = slap_NewMatrix(3, 4);
  for (int i = 0; i < slap_MatrixNumElements(&src); ++i) {
    src.data[i] = i * i - sqrt(i * 2.1);
  }
  Matrix dest = slap_NewMatrix(4, 3);
  slap_MatrixCopyTranspose(&dest, &src);
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.rows; ++j) {
      TEST(*slap_MatrixGetElement(&src, i, j) == *slap_MatrixGetElement(&dest, j, i));
    }
  }
  slap_FreeMatrix(&src);
  slap_FreeMatrix(&dest);
  return 1;
}

//#define LocalMatrix(rows, cols)

int StaticMatrix(void) {
  double Adata[25];
  Matrix A = {5, 5, Adata};
  TEST(A.rows == 5);
  return 1;
}

int main(void) {
  TestNewMatrix();
  SetConst();
  GetIndex();
  TestPrintMatrix();
  CopyMatrix();
  CopyTranspose();
  PrintTestResult();
  return TestResult();
}
