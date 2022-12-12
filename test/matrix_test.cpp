extern "C" {
  #include "matrix.h"
}

#include <math.h>

#include "gtest/gtest.h"

TEST(MatrixBasics, MatrixFromArray) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  EXPECT_EQ(slap_NumElements(A), 6);
  EXPECT_EQ(A.data, data);
  EXPECT_EQ(A.sx, 1);
  EXPECT_EQ(A.sy, 2);
  EXPECT_EQ(slap_NumRows(A), 2);
  EXPECT_EQ(slap_NumCols(A), 3);
}

TEST(MatrixBasics, NewMatrix) {
  Matrix mat = slap_NewMatrix(5, 4);
  EXPECT_EQ(mat.rows, 5);
  EXPECT_EQ(mat.cols, 4);
  EXPECT_EQ(slap_NumElements(mat), 20);
  slap_FreeMatrix(mat);
}

TEST(MatrixBasics, GetLinearIndex_2x3) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 0), 0);
  EXPECT_EQ(slap_GetLinearIndex(A, 1, 0), 1);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 1), 2);
  EXPECT_EQ(slap_GetLinearIndex(A, 1, 2), 5);
}

TEST(MatrixBasics, GetLinearIndex_3x2) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(3, 2, data);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 0), 0);
  EXPECT_EQ(slap_GetLinearIndex(A, 1, 0), 1);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 1), 3);
  EXPECT_EQ(slap_GetLinearIndex(A, 2, 1), 5);
}

TEST(MatrixBasics, GetLinearIndex_6x1) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(6, 1, data);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 0), 0);
  EXPECT_EQ(slap_GetLinearIndex(A, 1, 0), 1);
  EXPECT_EQ(slap_GetLinearIndex(A, 5, 0), 5);
}

TEST(MatrixBasics, GetLinearIndex_1x6) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(1, 6, data);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 0), 0);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 1), 1);
  EXPECT_EQ(slap_GetLinearIndex(A, 0, 5), 5);
}

TEST(MatrixBasics, CheckBounds_2x3) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  EXPECT_TRUE(slap_CheckInbounds(A, 0, 0));
  EXPECT_TRUE(slap_CheckInbounds(A, 1, 0));
  EXPECT_TRUE(slap_CheckInbounds(A, 0, 2));
  EXPECT_TRUE(slap_CheckInbounds(A, 1, 2));
  EXPECT_FALSE(slap_CheckInbounds(A, -1, 0));
  EXPECT_FALSE(slap_CheckInbounds(A, 0, -1));
  EXPECT_FALSE(slap_CheckInbounds(A, -1, -1));
  EXPECT_FALSE(slap_CheckInbounds(A, 0, 3));
  EXPECT_FALSE(slap_CheckInbounds(A, 2, 0));
}

TEST(MatrixBasics, CheckBounds_6x1) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(6, 1, data);
  EXPECT_TRUE(slap_CheckInbounds(A, 0, 0));
  EXPECT_TRUE(slap_CheckInbounds(A, 1, 0));
  EXPECT_TRUE(slap_CheckInbounds(A, 5, 0));
  EXPECT_FALSE(slap_CheckInbounds(A, -1, 0));
  EXPECT_FALSE(slap_CheckInbounds(A, 0, -1));
  EXPECT_FALSE(slap_CheckInbounds(A, -1, -1));
  EXPECT_FALSE(slap_CheckInbounds(A, 0, 1));
  EXPECT_FALSE(slap_CheckInbounds(A, 1, 1));
}

TEST(MatrixBasics, GetElement_2x3) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 2);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 1), 3);
  EXPECT_EQ(slap_GetElement(A, 0, 0), data);
  EXPECT_EQ(slap_GetElement(A, 1, 0), data + 1);
}

TEST(MatrixBasics, GetElement_3x2) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(3, 2, data);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 2);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 1), 4);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 1), 5);
}

TEST(MatrixBasics, GetElement_6x1) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(6, 1, data);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 2);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 2, 0), 3);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 5, 0), 6);
}

TEST(MatrixBasics, GetElement_1x6) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(1, 6, data);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 1), 2);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 2), 3);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 5), 6);
}

TEST(MatrixBasics, SetElement_2x3) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  slap_SetElement(A, 0, 0, 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 10);
  slap_SetElement(A, 1, 0, 11);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 11);
  slap_SetElement(A, 0, 1, 12);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 1), 12);
}

TEST(TransposeBasics, TransposeOp) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  Matrix At = slap_Transpose(A);
  EXPECT_TRUE(slap_IsTransposed(At));
  EXPECT_FALSE(slap_IsTransposed(A));
  EXPECT_EQ(slap_NumRows(At), 3);
  EXPECT_EQ(slap_NumCols(At), 2);
}

TEST(TransposeBasics, GetElement_2x3) {
  double data[6] = {1,2,3,4,5,6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  Matrix At = slap_Transpose(A);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 1, 0), 3);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 0, 1), 2);
}

TEST(TransposeBasics, SetElement_2x3) {
  double data[6] = {1, 2, 3, 4, 5, 6};
  Matrix A = slap_MatrixFromArray(2, 3, data);
  Matrix At = slap_Transpose(A);
  slap_SetElement(At, 0, 0, 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 0, 0), 10);
  slap_SetElement(At, 1, 0, 11);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 1, 0), 11);
  slap_SetElement(At, 0, 1, 12);
  EXPECT_DOUBLE_EQ(*slap_GetElement(At, 0, 1), 12);
}

TEST(MatrixAssignments, SetConst) {
  double data[6];
  Matrix A = slap_MatrixFromArray(2, 3, data);
  slap_SetConst(A, 10);
  for (int i = 0; i < slap_NumElements(A); ++i) {
    EXPECT_DOUBLE_EQ(data[i], 10);
  }
}

TEST(MatrixAssignments, Copy) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  double dataB[6];
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  Matrix B = slap_MatrixFromArray(2, 3, dataB);
  err = slap_MatrixCopy(B, A);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataB[i], dataA[i]);
  }
}

TEST(MatrixAssignments, CopyBadSize) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  double dataB[6] = {0, 0, 0, 0, 0, 0};
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  Matrix B = slap_MatrixFromArray(3, 2, dataB);
  err = slap_MatrixCopy(B, A);
  EXPECT_EQ(err, SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS);

  // Data shouldn't be changed
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataB[i], 0);
  }
}

TEST(MatrixAssignments, CopyTranspose) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  double dataB[6] = {0, 0, 0, 0, 0, 0};
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  Matrix B = slap_MatrixFromArray(3, 2, dataB);
  err = slap_MatrixCopyTranspose(B, A);
  EXPECT_EQ(err, SLAP_NO_ERROR);

  EXPECT_DOUBLE_EQ(*slap_GetElement(B, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(B, 1, 0), 3);
  EXPECT_DOUBLE_EQ(*slap_GetElement(B, 0, 1), 2);

  // Copy to transposed matrix
  double dataC[6] = {0, 0, 0, 0, 0, 0};
  Matrix C = slap_MatrixFromArray(2, 3, dataC);
  Matrix Ct = slap_Transpose(C);
  err = slap_MatrixCopyTranspose(Ct, A);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_DOUBLE_EQ(*slap_GetElement(Ct, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(Ct, 1, 0), 3);
  EXPECT_DOUBLE_EQ(*slap_GetElement(Ct, 0, 1), 2);

  EXPECT_DOUBLE_EQ(*slap_GetElement(C, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(C, 1, 0), 2);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataC[i], dataA[i]);
  }

  // Copy from transposed matrix
  double dataD[6] = {0, 0, 0, 0, 0, 0};
  Matrix D = slap_MatrixFromArray(2, 3, dataD);
  err = slap_MatrixCopyTranspose(D, slap_Transpose(A));
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_DOUBLE_EQ(*slap_GetElement(D, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(D, 1, 0), 2);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataD[i], dataA[i]);
  }
}

TEST(MatrixAssignments, CopyFromArray) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  double data[6] = {2, 4, 6, 7, 5, 3};
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  err = slap_MatrixCopyFromArray(A, data);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataA[i], data[i]);
  }
}

TEST(MatrixAssignments, CopyFromArray_BadPointer) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  double *data = NULL;
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  err = slap_MatrixCopyFromArray(A, data);
  EXPECT_EQ(err, SLAP_BAD_POINTER);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataA[i], i + 1);
  }
}

TEST(MatrixAssignments, SetIdentity) {
  double data[9];
  Matrix A = slap_MatrixFromArray(3, 3, data);
  const double val = 2.1;
  slap_SetIdentity(A, val);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j) {
        EXPECT_DOUBLE_EQ(*slap_GetElement(A, i, j), val);
      } else {
        EXPECT_DOUBLE_EQ(*slap_GetElement(A, i, j), 0);
      }
    }
  }
}

TEST(MatrixUnaryOps, MatrixScale) {
  enum slap_ErrorCode err;
  double dataA[6] = {1, 2, 3, 4, 5, 6};
  Matrix A = slap_MatrixFromArray(2, 3, dataA);
  err = slap_ScaleByConst(A, 3);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  for (int i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(dataA[i], 3 * (i + 1));
  }
}

//#include "simpletest/simpletest.h"

//int TestNewMatrix(void) {
//}
//
//int SetConst(void) {
//  Matrix mat = slap_NewMatrix(3, 4);
//  slap_SetConst(&mat, 5.0);
//  for (int i = 0; i < 12; ++i) {
//    TEST(mat.data[i] == 5);
//  }
//  slap_SetConst(&mat, -4.2);
//  for (int i = 0; i < 12; ++i) {
//    TEST(mat.data[i] == -4.2);
//  }
//  slap_FreeMatrix(mat);
//  return 1;
//}
//
//int GetIndex(void) {
//  Matrix mat = slap_NewMatrix(3, 4);
//  for (int i = 0; i < 12; ++i) {
//    mat.data[i] = i;
//  }
//  TEST(*slap_GetElement(mat, 0, 0) == 0);
//  TEST(*slap_GetElement(mat, 1, 0) == 1);
//  TEST(*slap_GetElement(mat, 0, 1) == 3);
//  TEST(*slap_GetElement(mat, 2, 3) == 11);
//  slap_FreeMatrix(mat);
//  return 1;
//}
//
////int TestPrintMatrix(void) {
////  Matrix mat = slap_NewMatrix(3, 4);
////  for (int i = 0; i < 12; ++i) {
////    mat.data[i] = i;
////  }
////  slap_PrintMatrix(mat);
////  slap_FreeMatrix(&mat);
////  return 1;
////}
////
////int CopyMatrix(void) {
////  Matrix src = slap_NewMatrix(10, 12);
////  for (int i = 0; i < slap_NumElements(&src); ++i) {
////    src.data[i] = i * i - sqrt(i * 2.1);
////  }
////  Matrix dest = slap_NewMatrix(10, 12);
////  slap_MatrixCopy(&dest, src);
////  for (int i = 0; i < slap_NumElements(&src); ++i) {
////    TEST(dest.data[i] == i * i - sqrt(i * 2.1));
////  }
////  slap_FreeMatrix(&src);
////  slap_FreeMatrix(&dest);
////  return 1;
////}
////
////int CopyTranspose(void) {
////  Matrix src = slap_NewMatrix(3, 4);
////  for (int i = 0; i < slap_NumElements(&src); ++i) {
////    src.data[i] = i * i - sqrt(i * 2.1);
////  }
////  Matrix dest = slap_NewMatrix(4, 3);
////  slap_MatrixCopyTranspose(&dest, &src);
////  for (int i = 0; i < src.rows; ++i) {
////    for (int j = 0; j < src.rows; ++j) {
////      TEST(*slap_GetElement(&src, i, j) == *slap_GetElement(&dest, j, i));
////    }
////  }
////  slap_FreeMatrix(&src);
////  slap_FreeMatrix(&dest);
////  return 1;
////}
//
////#define LocalMatrix(rows, cols)
//
////int StaticMatrix(void) {
////  double Adata[25];
////  Matrix A = {5, 5, Adata};
////  TEST(A.rows == 5);
////  return 1;
////}
//
//int main(void) {
//  TestNewMatrix();
//  SetConst();
//  GetIndex();
////  TestPrintMatrix();
////  CopyMatrix();
////  CopyTranspose();
//  PrintTestResult();
//  return TestResult();
//}
