//
//  BaseGenerator.h
//  Tonic
//
//  Created by Nick Donaldson on 5/30/13.
//  Copyright (c) 2013 Nick Donaldson. All rights reserved.
//

#ifndef __Tonic__BaseGenerator__
#define __Tonic__BaseGenerator__

#include "TonicCore.h"

namespace Tonic {
  
  namespace Tonic_ {
    
    //! Abstract base class for Generator and ControlGenerator
    /*!
        BaseGenerator_ contains common methods for input registration and context management
    */
    class BaseGenerator_
    {
      public:
        
        BaseGenerator_();
        virtual ~BaseGenerator_();
      
        void setSynthesisContext( const SynthesisContext_ & context ) { context_ = context; }
      
        virtual BaseGenerator_ * copy() = 0; // implemented one class up (Generator or ControlGenerator)
      
      // ---- Subclasses should implement -----
      
        virtual void reset() {}
      
        // -------------------------------------
      
      protected:
      
        // ---- Subclasses should implement -----
      
        virtual void computeOutput( const SynthesisContext_ & context ) {};
      
        // -------------------------------------

        SynthesisContext_                 context_;
        unsigned long                     lastFrameIndex_;
        
    };
    
  }
    
  class BaseGenerator : public TonicSmartPointer<Tonic_::BaseGenerator_>
  {
    public:
    
      BaseGenerator( Tonic_::BaseGenerator_ * gen = NULL ) : TonicSmartPointer<Tonic_::BaseGenerator_>(gen) {};
    
      void setSynthesisContext( const Tonic_::SynthesisContext_ & context ){
        obj->setSynthesisContext(context);
      }
  };
    
}



#endif /* defined(__Tonic__BaseGenerator__) */
