//
// Created by Brian Jackson on 3/2/23.
// Copyright (c) 2023 Robotic Exploration Lab. All rights reserved.
//

#include "slap/slap.h"

int main() {
  int n = 8;
  Matrix x = slap_NewMatrix(n, 1);
  Matrix y = slap_NewMatrix(n, 1);
  double dot = slap_InnerProduct(x, y);
  (void)dot;
}
