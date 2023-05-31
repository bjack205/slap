//
// Created by Brian Jackson on 5/31/2023.
// Copyright (c) 2023. All rights reserved.
//

#include <stdexcept>
#include <sstream>
#include "Mat.hpp"

namespace slap {

Mat &Mat::CatchErrors(enum slap_ErrorCode err) {
  if (err != SLAP_NO_ERROR) {
    std::stringstream ss;
    ss << "Error code " << err << " in Mat: " << slap_ErrorString(err);
    throw std::runtime_error(ss.str());
  }
  return *this;
}
}  // slap
