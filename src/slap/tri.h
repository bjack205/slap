//
// Created by Brian Jackson on 3/4/23.
// Copyright (c) 2023 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "slap/matrix.h"

enum slap_ErrorCode slap_UpperTriMulAdd(Matrix C, const Matrix U, const Matrix B,
                                        double alpha, double beta);

enum slap_ErrorCode slap_LowerTriMulAdd(Matrix C, const Matrix U, const Matrix B,
                                        double alpha, double beta);

bool slap_CheckUpperTri(const Matrix A);

bool slap_CheckLowerTri(const Matrix A);

enum slap_ErrorCode slap_MakeUpperTri(Matrix A);

enum slap_ErrorCode slap_MakeLowerTri(Matrix A);
