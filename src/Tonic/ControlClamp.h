//
//  ControlClamp.h
//  Tonic 
//
//  Created by Morgan Packard on 5/5/13.
//  Copyright (c) 2013 Nick Donaldson. All rights reserved.
//
// See LICENSE.txt for license and usage information.
//


#ifndef __Tonic__ControlClamp__
#define __Tonic__ControlClamp__

#include "ControlConditioner.h"

namespace Tonic {
  
  namespace Tonic_ {

    class ControlClamp_ : public ControlConditioner_{
    
    ControlGenerator min;
    ControlGenerator max;
      
    protected:
      void computeOutput(const SynthesisContext_ & context);
      
    public:
      ControlClamp_();
      ~ControlClamp_();
      
      void setMin(ControlGenerator gen){min = gen;};
      void setMax(ControlGenerator gen){max = gen;};
      
    };
    
  }
  
  class ControlClamp : public TemplatedControlConditioner<Tonic::ControlClamp, Tonic_::ControlClamp_>{
    
  public:
  
    createControlGeneratorSetters(ControlClamp, min, setMin);
    createControlGeneratorSetters(ControlClamp, max, setMax);

  };
}

#endif /* defined(__Tonic__ControlClamp__) */


