//
//  ControlGenerator.cpp
//  TonicDemo
//
//  Created by Morgan Packard on 2/12/13.

//

#ifndef TonicDemo_ControlGenerator_cpp
#define TonicDemo_ControlGenerator_cpp

#include "ControlGenerator.h"
#include "RampedValue.h"
#include <cmath>

namespace Tonic{

  RampedValue ControlGenerator::smoothed(float length){
    return RampedValue().length(length).target(*this);
  }
  
}

#endif
