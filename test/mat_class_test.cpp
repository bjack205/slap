//
// Created by Brian Jackson on 5/31/2023.
// Copyright (c) 2023. All rights reserved.
//

#include <limits>

#include "gtest/gtest.h"
#include "slap/Mat.hpp"
#include "slap/ConstMat.hpp"

using slap::Mat;

constexpr double kEps = std::numeric_limits<sfloat>::epsilon();

TEST(Mat, FromShared) {
  std::shared_ptr<sfloat[]> data(new sfloat[12]);
  Mat mat(3, 4, data);
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);
  EXPECT_EQ(mat.GetPtr(), data);
}

TEST(Mat, FromMatrixStruct) {
  std::shared_ptr<sfloat[]> data(new sfloat[12]);
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

TEST(Mat, SetDiagonal) {
  std::vector<sfloat> diag{1.2, 3.4, 5.6};
  sfloat val = -1;
  Mat mat = Mat::Create(3, 4).SetConst(-1).SetDiagonal(diag);
  for (int j = 0; j < mat.NumCols(); ++j) {
    for (int i = 0; i < mat.NumRows(); ++i) {
      if (i == j) {
        EXPECT_EQ(mat(i, j), diag[i]);
      } else {
        EXPECT_EQ(mat(i, j), val);
      }
    }
  }
  mat.Print();
}

TEST(Mat, Const_Mat) {
  const Mat mat = Mat::Create(3, 4).SetConst(1.2);

  // Check a few const getters
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);

  // Check indexing
  double val = mat(0, 0);
  EXPECT_NEAR(val, 1.2, kEps);
}

TEST(ConstMat, ConstMat) {
  const sfloat data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  slap::ConstMat mat(3, 4, data);

  // Check a few const getters
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);

  // Check indexing
  double val = mat(1, 0);
  EXPECT_NEAR(val, 2, kEps);
}

TEST(ConstMat, FromShared) {
  std::shared_ptr<sfloat[]> data(new sfloat[12]);
  slap::ConstMat mat(3, 4, data);
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);
  EXPECT_EQ(mat.GetPtr(), data);
}

TEST(ConstMat, FromConstShared) {
  const std::shared_ptr<const sfloat[]> data(new sfloat[12]);
  slap::ConstMat mat(3, 4, data);
  EXPECT_EQ(mat.NumRows(), 3);
  EXPECT_EQ(mat.NumCols(), 4);
  EXPECT_EQ(mat.GetPtr(), data);
}

TEST(Mat, Print) {
  Mat mat = Mat::Create(3, 4).SetRange(1, 12);  // NOLINT
  mat.Print();
}