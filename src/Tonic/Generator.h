//
//  Generator.h
//  Tonic
//
//  Created by Morgan Packard on 1/23/13.
//
//
// See LICENSE.txt for license and usage information.
//


#ifndef __Tonic__Generator__
#define __Tonic__Generator__

#include "BaseGenerator.h"
#include "TonicFrames.h"

namespace Tonic {

  namespace Tonic_{

    class Generator_ : public BaseGenerator_ {
      
      public:
        
        Generator_();
        
        virtual void tick( TonicFrames& frames, const SynthesisContext_ &context );
        
        bool isStereoOutput(){ return isStereoOutput_; };
        
        // set stereo/mono - changes number of channels in outputFrames_
        // subclasses should call in constructor to determine channel output
        virtual void setIsStereoOutput( bool stereo );
        
      protected:
        
        bool            isStereoOutput_;
        TonicFrames     outputFrames_;
      
    };
    
    inline void Generator_::tick(TonicFrames &frames, const SynthesisContext_ &context ){
      
      // check context to see if we need new frames
      if (context.forceNewOutput || lastFrameIndex_ != context.elapsedFrames){
        computeOutput(context);
        lastFrameIndex_ = context.elapsedFrames;
      }
    
      // copy synthesis block to frames passed in
      frames.copy(outputFrames_);
      
    }
    
    /////////////////////

    class PassThroughGenerator_ : public Tonic_::Generator_{
      public:
        void computeOutput( const SynthesisContext_ &context ) {};
    };

  }

  // ----
  
  class Generator : public BaseGenerator {

    public:
    
      Generator(Tonic_::Generator_ * gen = NULL) : BaseGenerator(gen) {}
    
      bool isStereoOutput(){
        return static_cast<Tonic_::Generator_*>(obj)->isStereoOutput();
      }
      
      virtual void tick(TonicFrames& frames, const Tonic_::SynthesisContext_ & context){
        static_cast<Tonic_::Generator_*>(obj)->tick(frames, context);
      }
  };
  
  // ----
  
  template<class GenType>
  class TemplatedGenerator : public Generator
  {
    protected:
      GenType* gen(){
        return static_cast<GenType*>(obj);
      }
    public:
      TemplatedGenerator() : Generator(new GenType) {}
  };
  
  // ----
  
  class PassThroughGenerator : public TemplatedGenerator<Tonic_::PassThroughGenerator_> {};
  
}

// Each generator should have three flavors of setter -- one that accepts a float, one that accepts a
// ControlGenerator, and one that accepts a Generator. This macro will automatically build those three
// setters

#include "FixedValue.h"

#define createGeneratorSetters(generatorClassName, methodNameInGenerator, methodNameInGenerator_) \
                                                                                        \
                                                                                        \
  generatorClassName& methodNameInGenerator(Generator arg){                             \
    this->gen()->methodNameInGenerator_(arg);                                           \
    this->gen()->registerInputGenerator(arg, #methodNameInGenerator);                   \
    return static_cast<generatorClassName&>(*this);                                     \
  }                                                                                     \
                                                                                        \
  generatorClassName& methodNameInGenerator(float arg){                                 \
    return methodNameInGenerator( FixedValue(arg) );                                    \
  }                                                                                     \
                                                                                        \
  generatorClassName& methodNameInGenerator(ControlGenerator arg){                      \
    return methodNameInGenerator(  FixedValue().setValue(arg) );                        \
  }



#endif /* defined(__Tonic__Generator__) */
