#include "errors.h"
#include "matrix.h"

const char* slap_ErrorString(enum slap_ErrorCode error_code) {
  char* msg;
  switch (error_code) {
    case SLAP_NO_ERROR:
      msg = "No Error";
      break;
    case SLAP_BAD_POINTER:
      msg = "Bad pointer to Matrix";
      break;
    case SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS:
      msg = "Incompatible matrix dimensions";
      break;
    case SLAP_BAD_MATRIX_DATA_POINTER:
      msg = "Bad matrix data pointer";
      break;
    case SLAP_INVALID_STRIDE:
      msg = "One of the matrix strides is less than 1";
      break;
    case SLAP_MATRIX_NOT_SQUARE:
      msg = "Invalid operation: Matrix needs to be square";
      break;
    case SLAP_MATRIX_NOT_DENSE:
      msg = "Operation only valid for dense matrices";
      break;
    default:
      msg = "Unknown error type";
  }
  return msg;
}