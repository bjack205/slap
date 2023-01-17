//
// Created by Brian Jackson on 12/19/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "slap/slap.h"
#include "gtest/gtest.h"

class SubMatrixTest : public ::testing::Test {
 public:
  double dataA[12];
  double dataB[12];
  Matrix A;
  Matrix B;
 protected:
  void SetUp() {
    A = slap_MatrixFromArray(3, 4, dataA);
    B = slap_MatrixFromArray(4, 3, dataB);
    for (int k = 0; k < 12; ++k) {
      dataA[k] = k + 1;
      dataB[k] = 2 * k + 1;
    }
  }
};

TEST_F(SubMatrixTest, SameMatrix) {
  slap_SetConst(A, 0);
  Matrix C = slap_CreateSubMatrix(A, 0, 0, 3, 4);
  EXPECT_FALSE(slap_IsNull(C));
  slap_SetConst(C, 10);
  EXPECT_DOUBLE_EQ(slap_Sum(A), 120);
}

TEST_F(SubMatrixTest, TopLeftCorner) {
  slap_SetConst(A, 0);
  Matrix C = slap_CreateSubMatrix(A, 0, 0, 2, 3);
  EXPECT_FALSE(slap_IsNull(C));
  EXPECT_EQ(slap_NumRows(C), 2);
  EXPECT_EQ(slap_NumCols(C), 3);
  slap_SetConst(C, 10);
  EXPECT_DOUBLE_EQ(slap_Sum(A), 60);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 2, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 2), 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 3), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 2, 3), 0);
  EXPECT_TRUE(true);
}

TEST_F(SubMatrixTest, BottomRightCorner) {
  slap_SetConst(A, 0);
  Matrix C = slap_CreateSubMatrix(A, 1, 1, 2, 3);
  EXPECT_FALSE(slap_IsNull(C));
  EXPECT_EQ(slap_NumRows(C), 2);
  EXPECT_EQ(slap_NumCols(C), 3);
  slap_SetConst(C, 10);
  EXPECT_DOUBLE_EQ(slap_Sum(A), 60);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 3), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 3), 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 2, 1), 10);

  // Set Diagonal
  slap_SetIdentity(C, 5);
  EXPECT_DOUBLE_EQ(slap_Sum(A), 10);
  EXPECT_TRUE(true);
}

TEST_F(SubMatrixTest, Middle) {
  slap_SetConst(A, 0);
  Matrix C = slap_CreateSubMatrix(A, 1, 1, 1, 2);
  EXPECT_FALSE(slap_IsNull(C));
  EXPECT_EQ(slap_NumRows(C), 1);
  EXPECT_EQ(slap_NumCols(C), 2);
  slap_SetConst(C, 10);
  EXPECT_DOUBLE_EQ(slap_Sum(A), 20);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 3), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 1), 10);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 2), 10);
}

TEST_F(SubMatrixTest, Transpose) {
  slap_SetConst(A, 0);
  Matrix C = slap_CreateSubMatrix(A, 1, 1, 2, 3);
  slap_SetRange(slap_Transpose(C), 1, 6);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 0), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 0, 1), 0);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 1), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 2, 1), 4);
  EXPECT_DOUBLE_EQ(*slap_GetElement(A, 1, 2), 2);

  EXPECT_DOUBLE_EQ(*slap_GetElement(C, 0, 0), 1);
  EXPECT_DOUBLE_EQ(*slap_GetElement(C, 1, 0), 4);
  EXPECT_DOUBLE_EQ(*slap_GetElement(C, 0, 1), 2);
  slap_PrintMatrix(A);
}
