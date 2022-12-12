#include "matrix_checks.h"

enum slap_ErrorCode slap_CheckMatrix(Matrix mat) {
  enum slap_ErrorCode err = SLAP_NO_ERROR;
  if (!mat.data) {
    err = SLAP_BAD_MATRIX_DATA_POINTER;
  } else if (mat.sx <= 0 || mat.sy <= 0) {
    err = SLAP_INVALID_STRIDE;
  }
  return err;
}

