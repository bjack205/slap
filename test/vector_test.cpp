//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include <math.h>

#include "slap/slap.h"
#include "slap/iterator.h"
#include "gtest/gtest.h"

#define DATA_LEN 6

class VectorTests : public ::testing::Test {
 public:
  sfloat data_x[DATA_LEN]     = {1, 0, -6, -10, 0.5, 1};  // NO LINT
  sfloat data_y[DATA_LEN + 3] = {5, 5,  4,   3, -2,  8, 8,-8, 9};
  Matrix x;
  Matrix y;
 protected:
   void SetUp() override {
     x = slap_MatrixFromArray(DATA_LEN, 1, data_x);
     y = slap_MatrixFromArray(DATA_LEN + 3, 1, data_y);
   }
};

TEST_F(VectorTests, ArgMax) {
  sfloat max_value;
  MatrixIterator max_index = slap_ArgMax(x, &max_value);
  EXPECT_DOUBLE_EQ(max_value, 1);
  EXPECT_EQ(max_index.k, 0);

  data_x[5] = 2;
  max_index = slap_ArgMax(x, NULL);
  EXPECT_EQ(max_index.k, 5);
}

TEST_F(VectorTests, ArgMin) {
  sfloat min_value;
  MatrixIterator min_index = slap_ArgMin(x, &min_value);
  EXPECT_DOUBLE_EQ(min_value, -10);
  EXPECT_EQ(min_index.k, 3);

  data_x[0] = -20;
  min_index = slap_ArgMin(x, NULL);
  EXPECT_EQ(min_index.k, 0);
}

TEST_F(VectorTests, Max) {
  EXPECT_DOUBLE_EQ(slap_Max(x), 1);
}

TEST_F(VectorTests, Min) {
  EXPECT_DOUBLE_EQ(slap_Min(x), -10);
}

TEST_F(VectorTests, NormTwoSquared) {
  sfloat norm_squared = 1 + 36 + 100 + 0.25 + 1;
  EXPECT_DOUBLE_EQ(slap_NormTwoSquared(x), norm_squared);
}

TEST_F(VectorTests, TwoNorm) {
  sfloat norm_squared = 1 + 36 + 100 + 0.25 + 1;
  EXPECT_DOUBLE_EQ(slap_NormTwo(x), sqrt(norm_squared));
}

TEST_F(VectorTests, OneNorm) {
  sfloat one_norm = 1 + 6 + 10 + 0.5 + 1;
  EXPECT_DOUBLE_EQ(slap_NormOne(x), one_norm);
}

TEST_F(VectorTests, InfNorm) {
  sfloat inf_norm = 10;
  EXPECT_DOUBLE_EQ(slap_NormInf(x), inf_norm);
}

TEST_F(VectorTests, Sum) {
  sfloat sum = 1 - 6 - 10 + 0.5 + 1;  // NOLINT
  EXPECT_DOUBLE_EQ(slap_Sum(x), sum);
}

TEST_F(VectorTests, InnerProduct) {
  sfloat dot = slap_InnerProduct(x, y);
  EXPECT_DOUBLE_EQ(5 - 24 - 30 - 1 + 8, dot);
}

TEST_F(VectorTests, QuadraticForm) {
  sfloat data_A[DATA_LEN * (DATA_LEN + 3)] = {1.0, -4.0, 1.0, -5.0, -9.0, 10.0, 5.0, 3.0, 8.0, 0.0, -6.0, 8.0, 1.0, 3.0, -7.0, -9.0, -2.0, -10.0, -3.0, -3.0, 9.0, 2.0, -8.0, 1.0, 0.0, 1.0, 1.0, -4.0, 0.0, 0.0, -8.0, -6.0, -8.0, 7.0, 7.0, -8.0, -2.0, -4.0, 0.0, -9.0, 9.0, -7.0, 0.0, -6.0, -8.0, 6.0, 10.0, -6.0, 8.0, 6.0, -6.0, 2.0, 9.0, 2.0};
  Matrix A = slap_MatrixFromArray(DATA_LEN + 3, DATA_LEN, data_A);
  sfloat dot = slap_QuadraticForm(y, A, x);
  EXPECT_DOUBLE_EQ(dot, 1522.5);
}

TEST_F(VectorTests, QuadraticForm_BadPointers) {
  sfloat data_A[DATA_LEN * (DATA_LEN + 3)] = {1.0, -4.0, 1.0, -5.0, -9.0, 10.0, 5.0, 3.0, 8.0, 0.0, -6.0, 8.0, 1.0, 3.0, -7.0, -9.0, -2.0, -10.0, -3.0, -3.0, 9.0, 2.0, -8.0, 1.0, 0.0, 1.0, 1.0, -4.0, 0.0, 0.0, -8.0, -6.0, -8.0, 7.0, 7.0, -8.0, -2.0, -4.0, 0.0, -9.0, 9.0, -7.0, 0.0, -6.0, -8.0, 6.0, 10.0, -6.0, 8.0, 6.0, -6.0, 2.0, 9.0, 2.0};
  Matrix A = slap_MatrixFromArray(DATA_LEN + 3, DATA_LEN, NULL);
  sfloat dot = slap_QuadraticForm(y, A, x);
  EXPECT_TRUE(isnan(dot));

  A.data = data_A;
  y.data = NULL;
  dot = slap_QuadraticForm(y, A, x);

  y.data = data_y;
  x.data = NULL;
  dot = slap_QuadraticForm(y, A, x);
}

TEST_F(VectorTests, OuterProduct) {
  sfloat data_C[DATA_LEN * (DATA_LEN + 3)] = {5.0, 5.0, 4.0, 3.0, -2.0, 8.0, 8.0, -8.0, 9.0, 0.0, 0.0, 0.0, 0.0, -0.0, 0.0, 0.0, -0.0, 0.0, -30.0, -30.0, -24.0, -18.0, 12.0, -48.0, -48.0, 48.0, -54.0, -50.0, -50.0, -40.0, -30.0, 20.0, -80.0, -80.0, 80.0, -90.0, 2.5, 2.5, 2.0, 1.5, -1.0, 4.0, 4.0, -4.0, 4.5, 5.0, 5.0, 4.0, 3.0, -2.0, 8.0, 8.0, -8.0, 9.0};
  Matrix C = slap_MatrixFromArray(DATA_LEN + 3, DATA_LEN, data_C);
  Matrix A = slap_NewMatrix(DATA_LEN + 3, DATA_LEN);
  slap_OuterProduct(A, y, x);
  EXPECT_LT(slap_MatrixNormedDifference(A, C), 1e-10);
  slap_FreeMatrix(&A);
}

TEST_F(VectorTests, CrossProduct_OutputTooShort) {
  enum slap_ErrorCode err;
  Matrix z = slap_NewMatrix(2, 1);
  err = slap_CrossProduct(z, x, y);
  if (slap_AssertionsEnabled())
    EXPECT_EQ(err, SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS);
  slap_FreeMatrix(&z);
}

TEST_F(VectorTests, CrossProduct) {
  enum slap_ErrorCode err;
  Matrix z = slap_NewMatrix(3, 1);
  err = slap_CrossProduct(z, x, y);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_DOUBLE_EQ(z.data[0], 30);
  EXPECT_DOUBLE_EQ(z.data[1], -34);
  EXPECT_DOUBLE_EQ(z.data[2], 5);

  err = slap_CrossProduct(z, y, x);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_DOUBLE_EQ(z.data[0], -30);
  EXPECT_DOUBLE_EQ(z.data[1], +34);
  EXPECT_DOUBLE_EQ(z.data[2], -5);
  slap_FreeMatrix(&z);
}
