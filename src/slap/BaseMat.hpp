//
// Created by Brian Jackson on 6/1/2023.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#pragma once

#include <memory>

#include "slap/slap.h"

namespace slap {

class BaseMat {
 protected:
  // Set Constructor to protected so that only derived classes can use it
  BaseMat(struct Matrix mat) : mat_(mat) {}

 public:
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
  size_t size() const { return NumElements(); }

  // Data Access
  const sfloat *data() const { return slap_GetData(mat_); }
  const sfloat &operator()(int i, int j) const { return *slap_GetElement(mat_, i, j); }

  sfloat NormTwo() const { return slap_NormTwo(mat_); }
  sfloat NormOne() const { return slap_NormOne(mat_); }
  sfloat NormInf() const { return slap_NormInf(mat_); }
  sfloat NormTwoSquared() const { return slap_NormTwoSquared(mat_); }

  // Misc
  void Print() const { slap_PrintMatrix(mat_); }
  void Print(std::string name) const;

 protected:
  struct Matrix mat_;
};

} // slap

