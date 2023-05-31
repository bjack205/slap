//
// Created by Brian Jackson on 6/1/2023.
// Copyright (c) 2023. All rights reserved.
//
#pragma once

#include "slap/BaseMat.hpp"

namespace slap {

class ConstMat : public BaseMat {
 public:
  // Constructors
  ConstMat() : BaseMat(slap_NullMatrix()), data_(nullptr) {}
  ConstMat(struct Matrix mat, std::shared_ptr<const sfloat[]> data)
      : BaseMat(mat), data_(data) {}
  ConstMat(int nrows, int ncols, std::shared_ptr<const sfloat[]> data)
      : BaseMat(slap_MatrixFromArray(nrows, ncols, const_cast<sfloat *>(data.get()))), data_(data) {}

  // These methods do not take ownership of the data pointer
  ConstMat(int rows, int cols, const double *data)
      : BaseMat(slap_MatrixFromArray(rows, cols, const_cast<sfloat *>(data))) {}

  // Data Access
  const sfloat *GetData() const { return slap_GetData(mat_); }
  const std::shared_ptr<const sfloat[]> &GetPtr() const { return data_; }

 private:
  std::shared_ptr<const sfloat[]> data_;
};

}  // slap