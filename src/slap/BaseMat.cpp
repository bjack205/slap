//
// Created by Brian Jackson on 6/1/2023.
// Copyright (c) 2023 Albedo. All rights reserved.
//

#include "Mat.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "BaseMat.hpp"

void slap::BaseMat::Print(std::string name) const {
  std::cout << "Matrix " << name << ": [\n";
  Print();
  std::cout << "]\n";
}
