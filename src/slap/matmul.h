//
// Created by Brian Jackson on 12/19/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

enum slap_ErrorCode slap_MatMulAdd(Matrix C, Matrix A, Matrix B, double alpha, double beta);

enum slap_ErrorCode slap_MatMulAB(Matrix C, Matrix A, Matrix B);
enum slap_ErrorCode slap_MatMulAtB(Matrix C, Matrix A, Matrix B);
