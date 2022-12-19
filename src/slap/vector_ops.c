//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "vector_ops.h"

#include <math.h>

int slap_ArgMax(Matrix mat, double* max_value) {
  int max_index = -1;
  double value = -INFINITY;
  double value_i;
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    value_i = mat.data[i];
    if (value_i > value) {
      value = value_i;
      max_index = i;
    }
  }
  if (max_value)
    *max_value = value;
  return max_index;
}

double slap_Max(Matrix mat) {
  double max_value;
  slap_ArgMax(mat, &max_value);
  return max_value;
}

int slap_ArgMin(Matrix mat, double* min_value) {
  int min_index = -1;
  double value = +INFINITY;
  double value_i;
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    value_i = mat.data[i];
    if (value_i < value) {
      value = value_i;
      min_index = i;
    }
  }
  if (min_value)
    *min_value = value;
  return min_index;
}

double slap_Min(Matrix mat) {
  double min_value;
  slap_ArgMin(mat, &min_value);
  return min_value;
}

double slap_NormTwoSquared(Matrix mat) {
  double value = 0;
  double value_i;
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    value_i = mat.data[i];
    value += value_i * value_i;
  }
  return value;
}

double slap_NormTwo(Matrix mat) {
  double norm_squared = slap_NormTwoSquared(mat);
  return sqrt(norm_squared);
}

double slap_NormInf(Matrix mat) {
  double value = 0;
  double value_i;
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    value_i = fabs(mat.data[i]);
    if (value_i > value) {
      value = value_i;
    }
  }
  return value;
}

double slap_NormOne(Matrix mat) {
  double value = 0;
  double value_i;
  for (int i = 0; i < slap_NumElements(mat); ++i) {
    value_i = fabs(mat.data[i]);
    value += value_i;
  }
  return value;
}

