#include "errors.h"

#include <stdarg.h>

#include "matrix.h"

static FILE* slap_OUTPUT_FILE = NULL;

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
    case SLAP_INVALID_DIMENSION:
      msg = "Matrix dimensions must be non-negative";
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
    case SLAP_CHOLESKY_FAIL:
      msg = "Cholesky factorization failed. Matrix likely not positive definite";
      break;
    case SLAP_INVALID_MATRIX:
      msg = "Invalid matrix. Check for NULL data pointer and a stride of 0";
      break;
    case SLAP_INDEX_OUT_OF_BOUNDS:
      msg = "Indexing operation out of bounds";
      break;
    default:
      msg = "Unknown error type";
  }
  return msg;
}

#ifdef NDEBUG

enum slap_ErrorCode slap_PrintError(enum slap_ErrorCode error_code, const char* file, int line_number,
                                    const char* format, ...) {
  (void)file;
  (void)line_number;
  (void)format;
  return error_code;
}

void slap_SetOutputFile(FILE* file) {
    (void)file;
}

FILE* slap_GetOutputFile(void) {
    slap_OUTPUT_FILE = NULL;
    return slap_OUTPUT_FILE;
}

int slap_AssertionsEnabled(void) { return false; }

#else

enum slap_ErrorCode slap_PrintError(enum slap_ErrorCode error_code, const char* file, int line_number,
                     const char* format, ...) {
  va_list args;
  va_start(args, format);
  if (slap_OUTPUT_FILE == NULL) {
    slap_OUTPUT_FILE = stderr;
  }
  if (slap_OUTPUT_FILE == stderr) {
    fprintf(slap_OUTPUT_FILE, SLAP_COLOR_RED);
  }
  fprintf(slap_OUTPUT_FILE, "slap Error %d: %s\n", (int)error_code,
          slap_ErrorString(error_code));
  fprintf(slap_OUTPUT_FILE, "               ");
  vfprintf(slap_OUTPUT_FILE, format, args);
  if (slap_OUTPUT_FILE == stderr) {
    fprintf(slap_OUTPUT_FILE, SLAP_COLOR_NORMAL);
  }
  fprintf(slap_OUTPUT_FILE, " (%s:%d)\n", file, line_number);
  va_end(args);
  return error_code;
}
void slap_SetOutputFile(FILE* file) {
  slap_OUTPUT_FILE = file;
}
FILE* slap_GetOutputFile(void) { return slap_OUTPUT_FILE; }

int slap_AssertionsEnabled(void) { return true; }

#endif
