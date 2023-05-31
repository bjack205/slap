//
// Created by Brian Jackson on 5/31/2023.
// Copyright (c) 2023. All rights reserved.
//

#pragma once

#include "slap/BaseMat.hpp"

namespace slap {

class Mat : public BaseMat {
 public:
  // Constructors
  Mat() : BaseMat(slap_NullMatrix()), data_(nullptr) {}
  Mat(struct Matrix mat, std::shared_ptr<sfloat[]> data) : BaseMat(mat), data_(std::move(data)) { mat_.data = data_.get(); }
  Mat(int nrows, int ncols, std::shared_ptr<sfloat[]> data)
      : BaseMat(slap_MatrixFromArray(nrows, ncols, data.get())), data_(std::move(data)) {}

  // These methods do not take ownership of the data pointer
  explicit Mat(struct Matrix mat) : BaseMat(mat), data_(nullptr) {}
  Mat(int nrows, int ncols, sfloat *data) : BaseMat(slap_MatrixFromArray(nrows, ncols, data)), data_(nullptr) {}

  // Allocating Constructor
  static Mat Create(int nrows, int ncols) {
    std::shared_ptr<sfloat[]> data(new sfloat[nrows * ncols]);
    return {nrows, ncols, data};
  }

  // Data Access
  sfloat *GetData() { return slap_GetData(mat_); }
  const sfloat *GetData() const { return slap_GetData(mat_); }
  std::shared_ptr<sfloat[]> &GetPtr() { return data_; }
  const std::shared_ptr<sfloat[]> &GetPtr() const { return data_; }
  using BaseMat::operator();
  sfloat &operator()(int i, int j) { return *slap_GetElement(mat_, i, j); }

  // Methods to match stl containers
  sfloat *data() { return slap_GetData(mat_); }

  // Transformations
  Mat Flatten() { return {slap_Flatten(mat_), data_}; }
  Mat Transpose() { return {slap_Transpose(mat_), data_}; }
  Mat UpperTri() { return {slap_UpperTri(mat_), data_}; }
  Mat LowerTri() { return {slap_LowerTri(mat_), data_}; }
  Mat Reshape(int nrows, int ncols) { return {slap_Reshape(mat_, nrows, ncols), data_}; }

  // Unary operations
  Mat &SetConst(sfloat val) { return CatchErrors(slap_SetConst(mat_, val)); }
  Mat &SetZero() { return CatchErrors(slap_SetConst(mat_, 0)); }
  Mat &ScaleByConst(sfloat alpha) { return CatchErrors(slap_ScaleByConst(mat_, alpha)); }
  Mat &SetIdentity(sfloat val = 1) { return CatchErrors(slap_SetIdentity(mat_, val)); }
  Mat &AddIdentity(sfloat val = 1) { return CatchErrors(slap_AddIdentity(mat_, val)); }
  Mat &SetRange(sfloat start, sfloat step) { return CatchErrors(slap_SetRange(mat_, start, step)); }

  template<class Vector>
  Mat &SetDiagonal(const Vector &vec) {
    return CatchErrors(slap_SetDiagonal(mat_, vec.data(), vec.size()));
  }

  Mat &CatchErrors(enum slap_ErrorCode err);
 private:
  std::shared_ptr<sfloat[]> data_;
};

}  // slap
