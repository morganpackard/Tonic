//
//  FilteredNoise.h
//  TonicDemo
//
//  Created by Morgan Packard on 2/24/13.

//

/*
Because of the fancy registerSynth macro, and because this synth has the same interface
as Synth it's not necessary to create a header file. You can create an instance of this synth using 
SynthFactory::createInstance(SYNTH_NAME), where SYNTH_NAME is the name supplied to registerSynth.
*/

#ifndef TonicDemo_FilteredNoise_h
#define TonicDemo_FilteredNoise_h

#include "Tonic.h"

using namespace Tonic;

class FilteredNoiseSynth : public Synth{
public:
  FilteredNoiseSynth(){
    vector<float> midiNums;
    midiNums.push_back(-24);
    midiNums.push_back(0);
    midiNums.push_back(3);
    midiNums.push_back(7);
    midiNums.push_back(10);
    
    const float cutoffMult = 100;
    
    PinkNoise noise = PinkNoise();
    
    ControlGenerator cutoffCtrl = addParameter("cutoff", 0.5);
    
    Generator q_v = addParameter("Q", 5).smoothed();
    
    Adder sumOfFilters;
    
    ControlGenerator toothyBassChangeTrigger = ControlMetro().bpm( ControlRandom().min(3).max(10).trigger( ControlMetro().bpm(100) ));
    ControlGenerator lowBasFreq =   ControlFloor().in( midiNums.at(0) + 12 + cutoffCtrl * cutoffMult ) >> ControlMidiToFreq();
    ControlGenerator lowBasFreq2 =   ControlFloor().in( midiNums.at(0) + 12 + cutoffCtrl * cutoffMult  + 0.01) >> ControlMidiToFreq();
    ControlGenerator fmAmt = ControlValue(0.1);
    Generator cutoffSlowSwell = (SineWave().freq(0.1) + 1.0f) * 500;
    cutoffSlowSwell = FixedValue(500);
    Generator lpfCutoff = 100 + (cutoffSlowSwell + 0.5 * SineWave().freq( ControlRandom().min(0.001).max(50).trigger(toothyBassChangeTrigger) ) * cutoffSlowSwell);
    Generator lpfCutoff2 = 100 + (cutoffSlowSwell + 0.5 * SineWave().freq( ControlRandom().min(0.001).max(50).trigger(toothyBassChangeTrigger) ) * cutoffSlowSwell);
   
    ControlGenerator toothyBassRandomAmp = ControlRandom()
        .min(-3)
        .max(1)
        .trigger(toothyBassChangeTrigger)
        >> ControlClamp().min(0).max(1)
        ;
    
    Generator toothyBassSwell = ( (toothyBassRandomAmp * toothyBassRandomAmp * toothyBassRandomAmp * 5) ).smoothed(10);
    
    Generator lowToothyBass =
      RectWave()
      .freq(  lowBasFreq )
      .pwm(  0.5 + 0.2 * (SineWave().freq(0.013) + 1)  );
    
    
    Generator lowToothyBass2 =
      RectWave()
      .freq(  lowBasFreq2 )
      .pwm(  0.5 + 0.2 * (SineWave().freq(0.013) + 1)  );
    
    
    LPF12 filterL = LPF12().cutoff(lpfCutoff);
    LPF12 filterR = LPF12().cutoff(lpfCutoff2);
    
    
    lowToothyBass = MonoToStereoPanner().pan(-1).input( filterL.input( lowToothyBass ))
      +
    MonoToStereoPanner().pan(1).input( filterR.input( lowToothyBass2 ));
    
    lowToothyBass = lowToothyBass * toothyBassSwell;
    
    for(int i = 0; i < midiNums.size(); i++){
      Generator tremelo = (SineWave().freq( randomFloat(0.1, 0.3) ) + 1.5) * 0.3;
      Generator cutoff = ControlMidiToFreq().in( ControlFloor().in( midiNums.at(i) + cutoffCtrl * cutoffMult  )).smoothed().length(0.01);
      BPF24 filter = BPF24().Q( q_v ).cutoff( cutoff );
      sumOfFilters = sumOfFilters + (noise >> filter) * tremelo;
    }
    
    // add a bit of gain for higher Q
    // Using this to test output limiter as well - this will probably clip/wrap if limiter is not working
    outputGen =
    sumOfFilters * (1 + q_v * 0.05)
    +
      lowToothyBass * 0.05;
    
    
    
  }
};

registerSynth(FilteredNoiseSynth);

#endif
