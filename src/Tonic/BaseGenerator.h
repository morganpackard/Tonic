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
  
  // forward declaration
  class BaseGenerator;
  
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
      
        BaseGenerator getInputGenerator( string name );
        void registerInputGenerator( BaseGenerator inputGen, string name );
      
      protected:
        
        virtual void computeOutput( const SynthesisContext_ & context ) = 0;

        SynthesisContext_                 context_;
        std::map<string, BaseGenerator>   inputGenerators_;
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
    
      void registerInputGenerator( BaseGenerator inputGen, string name ){
        obj->registerInputGenerator(inputGen, name);
      }
  };
  
}

#endif /* defined(__Tonic__BaseGenerator__) */
