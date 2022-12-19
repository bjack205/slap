//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

typedef struct MatrixIterator {
  uint16_t len;    // TODO (brian): safeguard against integer overflow
  uint16_t rows;
  uint16_t dx;     // index delta for movement in x
  uint16_t dy;     // index delta for movement in y
  uint16_t i;      // row index
  uint16_t j;      // column index
  uint16_t k;      // linear index
  uint16_t index;  // memory index
} MatrixIterator;

MatrixIterator slap_Iterator(Matrix mat);

int slap_Step(MatrixIterator *iterator);

static inline bool slap_IsFinished(const MatrixIterator *iterator) {
  return iterator->k >= iterator->len;
}
