//
// Created by Brian Jackson on 12/18/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include "matrix.h"

int slap_ArgMax(Matrix mat, double *max_value);

int slap_ArgMin(Matrix mat, double *min_value);

double slap_Max(Matrix mat);

double slap_Min(Matrix mat);

double slap_NormTwoSquared(Matrix mat);

double slap_NormTwo(Matrix mat);

double slap_NormInf(Matrix mat);

double slap_NormOne(Matrix mat);
