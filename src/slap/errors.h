#pragma once

enum slap_ErrorCode {
  SLAP_NO_ERROR = 0,
  SLAP_BAD_POINTER,
  SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS,
  SLAP_BAD_MATRIX_DATA_POINTER,
  SLAP_INVALID_DIMENSION,
  SLAP_INVALID_STRIDE,
  SLAP_MATRIX_NOT_SQUARE,
  SLAP_MATRIX_NOT_DENSE,
};

const char* slap_ErrorString(enum slap_ErrorCode error_code);


// TODO (brian): Add compile option to turn this on/off
#include <stdio.h>
#define SLAP_COLOR_RED "\x1b[31m"
#define SLAP_THROW_ERROR(error_code, message) \
  ((fprintf(stderr, SLAP_COLOR_RED "slap Error %d: %s\n", (int)error_code, slap_ErrorString(error_code)), \
  fprintf(stderr, SLAP_COLOR_RED "              %s (%s:%d)\n", message, __FILE__, __LINE__)), \
  error_code)
//static enum slap_ErrorCode SLAP_ERRNO = SLAP_NO_ERROR;