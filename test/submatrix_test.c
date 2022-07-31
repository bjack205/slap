#include "slap/submatrix.h"

#include "slap/matrix.h"
#include "simpletest/simpletest.h"

int CreateSubArray() {
  Matrix mat = slap_NewMatrixZeros(10,10);
  SubMatrix submat = slap_SubMatrixFromMatrix(1,1,3,3, &mat);
  TEST(submat.data == mat.data + 11);
  TEST(submat.rows == 3);
  TEST(submat.cols == 3);
  slap_FreeMatrix(&mat);
  return 1;
}

int SubMatrixSetConst() {
  Matrix mat = slap_NewMatrixZeros(5,5);
  SubMatrix submat = slap_SubMatrixFromMatrix(1,1,3,4, &mat);
  slap_SubMatrixSetConst(&submat, 1.0);
  // clang-format off
  double data[25] = {
    0,0,0,0,0,
    0,1,1,1,0,
    0,1,1,1,0,
    0,1,1,1,0,
    0,1,1,1,0,
  };
  // clang-format on
  Matrix ans = slap_MatrixFromArray(5,5,data);
  TEST(slap_MatrixNormedDifference(&ans, &mat) < 1e-10); 
  slap_FreeMatrix(&mat);
  return 1;
}

int SubMatrixSetIdentity() {
  Matrix mat = slap_NewMatrixZeros(5,5);
  SubMatrix submat = slap_SubMatrixFromMatrix(2,1,3,3, &mat);
  slap_SubMatrixSetIdentity(&submat, 3);
  // clang-format off
  double data[25] = {
    0,0,0,0,0,
    0,0,3,0,0,
    0,0,0,3,0,
    0,0,0,0,3,
    0,0,0,0,0,
  };
  // clang-format on
  Matrix ans = slap_MatrixFromArray(5,5,data);
  TEST(slap_MatrixNormedDifference(&ans, &mat) < 1e-10); 
  slap_FreeMatrix(&mat);
  return 1;
}

int main() {
  CreateSubArray();
  SubMatrixSetConst();
  SubMatrixSetIdentity();
  PrintTestResult();
  return TestResult();
}
