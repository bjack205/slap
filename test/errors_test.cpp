//
// Created by Brian Jackson on 3/2/23.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#include "gtest/gtest.h"
#include "slap/slap.h"

TEST(ErrorTests, ErrorString) {
  (void)SLAP_ERROR(SLAP_CHOLESKY_FAIL, "Got Message %s", "Hello, mate!");
  fprintf(stderr, "Something\n");
}

TEST(ErrorTests, OutputToFile) {
  FILE* fid = fopen("slap.log", "w");
  slap_SetOutputFile(fid);
  (void)SLAP_ERROR(SLAP_INDEX_OUT_OF_BOUNDS, "Out of bounds with index %d", 10 + 1);
  fclose(fid);
}