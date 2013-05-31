//
//  BaseGenerator.cpp
//  Tonic
//
//  Created by Nick Donaldson on 5/30/13.
//  Copyright (c) 2013 Nick Donaldson. All rights reserved.
//

#include "BaseGenerator.h"

namespace Tonic {
  
  namespace Tonic_ {
    
    BaseGenerator_::BaseGenerator_() : lastFrameIndex_(0) {}
    
    BaseGenerator_::~BaseGenerator_() {}
    
    void BaseGenerator_::registerInputGenerator(BaseGenerator inputGen, string name){
      inputGenerators_[name] = inputGen;
    }
    
  }

}