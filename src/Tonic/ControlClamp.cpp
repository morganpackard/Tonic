//
//  ControlClamp.cpp
//  Tonic
//
//  Created by Morgan Packard on 5/5/13.
//  Copyright (c) 2013 Nick Donaldson. All rights reserved.
//

#include "ControlClamp.h"

namespace Tonic { namespace Tonic_{
  
  ControlClamp_::ControlClamp_(){
    
  }
  
  ControlClamp_::~ControlClamp_(){
    
  }
  
  void ControlClamp_::computeOutput(const SynthesisContext_ & context){
    ControlGeneratorOutput minOut = min.tick(context);
    ControlGeneratorOutput maxOut = max.tick(context);
    ControlGeneratorOutput inputOut = input_.tick(context);
    TonicFloat newOutVal =  clamp(inputOut.value, minOut.value, maxOut.value);
    lastOutput_.status = newOutVal == lastOutput_.value ?  ControlGeneratorStatusHasChanged : ControlGeneratorStatusHasNotChanged;
    lastOutput_.value = newOutVal;
  }
  
  
  
} // Namespace Tonic_
  
  
  
} // Namespace Tonic
