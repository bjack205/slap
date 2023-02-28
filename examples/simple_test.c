//
// Created by Brian Jackson on 2/27/23.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#include "slap/slap.h"

int main(void) {
  double data[12];
  Matrix mat = slap_MatrixFromArray(3,4,data);
  mat.rows = 0;
  (void)mat;
  return 0;
}
