//
// Created by Brian Jackson on 5/31/2023.
// Copyright (c) 2023. All rights reserved.
//

#include "gtest/gtest.h"

#include "slap/Mat.hpp"

using slap::Mat;

TEST(Mat, FromShared) {
  std::shared_ptr<sfloat> data(new sfloat[12]);
  Mat mat(3, 4, data);
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);
  EXPECT_EQ(mat.GetPtr(), data);
}

TEST(Mat, FromMatrixStruct) {
  std::shared_ptr<sfloat> data(new sfloat[12]);
  struct Matrix mat{};
  mat.rows = 3;
  mat.cols = 4;
  mat.data = data.get();
  EXPECT_EQ(data.use_count(), 1);
  {
    Mat mat_class(mat, data);
    EXPECT_EQ(mat_class.NumRows(), 3);
    EXPECT_EQ(mat_class.NumCols(), 4);
    EXPECT_EQ(mat_class.GetPtr(), data);
    EXPECT_EQ(data.use_count(), 2);
  }
  EXPECT_EQ(data.use_count(), 1);
}

TEST(Mat, SetZero) {
  Mat mat = Mat::Create(3, 4).SetZero();
  for (int j = 0; j < mat.NumCols(); ++j) {
    for (int i = 0; i < mat.NumRows(); ++i) {
      EXPECT_EQ(mat(i, j), 0);
    }
  }
}

TEST(Mat, SetConst) {
  const sfloat val = 1.2;
  Mat mat = Mat::Create(3, 4).SetConst(val);
  for (int j = 0; j < mat.NumCols(); ++j) {
    for (int i = 0; i < mat.NumRows(); ++i) {
      EXPECT_EQ(mat(i, j), val);
    }
  }
}