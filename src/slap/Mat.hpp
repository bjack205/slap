//
// Created by Brian Jackson on 5/31/2023.
// Copyright (c) 2023. All rights reserved.
//

#pragma once

#include <memory>

#include "slap.h"

namespace slap {

class Mat {
 public:
  // Constructors
  Mat() : mat_(slap_NullMatrix()), data_(nullptr) {}
  Mat(struct Matrix mat, std::shared_ptr<sfloat> data) : mat_(mat), data_(std::move(data)) { mat_.data = data_.get(); }
  Mat(int nrows, int ncols, std::shared_ptr<sfloat> data)
      : mat_(slap_MatrixFromArray(nrows, ncols, data.get())), data_(std::move(data)) {}

  // Allocating Constructor
  static Mat Create(int nrows, int ncols) {
    std::shared_ptr<sfloat> data(new sfloat[nrows * ncols]);
    return {nrows, ncols, data};
  }

  // Dimensions
  int NumRows() const { return slap_NumRows(mat_); }
  int NumCols() const { return slap_NumCols(mat_); }
  int MinDim() const { return slap_MinDim(mat_); }
  int NumElements() const { return slap_NumElements(mat_); }
  int Stride() const { return slap_Stride(mat_); }

  // Boolean Checks
  bool IsNull() const { return slap_IsNull(mat_); }
  bool IsTransposed() const { return slap_IsTransposed(mat_); }
  bool IsEmpty() const { return slap_IsEmpty(mat_); }
  bool IsSquare() const { return slap_IsSquare(mat_); }
  bool IsDense() const { return slap_IsDense(mat_); }

  // Data Access
  sfloat *GetData() { return slap_GetData(mat_); }
  std::shared_ptr<sfloat> GetPtr() { return data_; }
  sfloat &operator()(int i, int j) { return *slap_GetElement(mat_, i, j); }
  const sfloat &operator()(int i, int j) const { return *slap_GetElement(mat_, i, j); }

  // Methods to match stl containers
  sfloat *data() { return slap_GetData(mat_); }
  size_t size() const { return NumElements(); }

  // Transformations
  Mat Flatten() { return {slap_Flatten(mat_), data_}; }
  Mat Transpose() { return {slap_Transpose(mat_), data_}; }
  Mat UpperTri() { return {slap_UpperTri(mat_), data_}; }
  Mat LowerTri() { return {slap_LowerTri(mat_), data_}; }
  Mat Reshape(int nrows, int ncols) { return {slap_Reshape(mat_, nrows, ncols), data_}; }

  // Unary operations
  Mat& SetConst(sfloat val) { return CatchErrors(slap_SetConst(mat_, val)); }
  Mat& SetZero() { return CatchErrors(slap_SetConst(mat_, 0)); }
  Mat& ScaleByConst(sfloat alpha) { return CatchErrors(slap_ScaleByConst(mat_, alpha)); }
  Mat& SetIdentity(sfloat val = 1) { return CatchErrors(slap_SetIdentity(mat_, val)); }
  Mat& AddIdentity(sfloat val = 1) { return CatchErrors(slap_AddIdentity(mat_, val)); }
  Mat& SetRange(sfloat start, sfloat step) { return CatchErrors(slap_SetRange(mat_, start, step)); }

  template <class Vector>
  enum slap_ErrorCode SetDiagonal(const Vector &vec) {
    return slap_SetDiagonal(mat_, vec.data(), vec.size());
  }

 private:
  Mat& CatchErrors(enum slap_ErrorCode err);
  struct Matrix mat_;
  std::shared_ptr<sfloat> data_;
};

}  // slap
