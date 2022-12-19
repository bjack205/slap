#pragma once
#include "matrix.h"

#define SLAP_CHECK_MATRIX(mat)                                      \
  {                                                                 \
    enum slap_ErrorCode _err_ = slap_CheckMatrix(mat);                \
    if (_err_ != SLAP_NO_ERROR)                                       \
      return SLAP_THROW_ERROR(_err_, "Matrix failed validity check"); \
  }

#define SLAP_ASSERT_SQUARE(mat, msg) if (!slap_IsSquare(mat)) return SLAP_THROW_ERROR(SLAP_MATRIX_NOT_SQUARE, msg)

enum slap_ErrorCode slap_CheckMatrix(Matrix mat);

