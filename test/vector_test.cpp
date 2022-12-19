//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include <math.h>

#include "slap/slap.h"
#include "gtest/gtest.h"

#define DATA_LEN 6

class VectorTests : public ::testing::Test {
 public:
  double data[DATA_LEN] = {1, 0, -6, -10, 0.5, 1};  // NO LINT
  Matrix x;
 protected:
   void SetUp() override {
     x = slap_MatrixFromArray(DATA_LEN, 1, data);
   }
};

TEST_F(VectorTests, ArgMax) {
  double max_value;
  MatrixIterator max_index = slap_ArgMax(x, &max_value);
  EXPECT_DOUBLE_EQ(max_value, 1);
  EXPECT_EQ(max_index.k, 0);

  data[5] = 2;
  max_index = slap_ArgMax(x, NULL);
  EXPECT_EQ(max_index.k, 5);
}

TEST_F(VectorTests, ArgMin) {
  double min_value;
  MatrixIterator min_index = slap_ArgMin(x, &min_value);
  EXPECT_DOUBLE_EQ(min_value, -10);
  EXPECT_EQ(min_index.k, 3);

  data[0] = -20;
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
  double norm_squared = 1 + 36 + 100 + 0.25 + 1;
  EXPECT_DOUBLE_EQ(slap_NormTwoSquared(x), norm_squared);
}

TEST_F(VectorTests, TwoNorm) {
  double norm_squared = 1 + 36 + 100 + 0.25 + 1;
  EXPECT_DOUBLE_EQ(slap_NormTwo(x), sqrt(norm_squared));
}

TEST_F(VectorTests, OneNorm) {
  double one_norm = 1 + 6 + 10 + 0.5 + 1;
  EXPECT_DOUBLE_EQ(slap_NormOne(x), one_norm);
}

TEST_F(VectorTests, InfNorm) {
  double inf_norm = 10;
  EXPECT_DOUBLE_EQ(slap_NormInf(x), inf_norm);
}