/*
  ==============================================================================

    dplusClipper.cpp
    Created: 1 Aug 2024 11:02:54pm
    Author:  Sohyun

  ==============================================================================
*/

#include "dplusClipper.h"
#include <JuceHeader.h>

float dplusClipper::processSample(float Vi){

    int i = 1;
    float fVd = 2*Is*sinh(Vd/(eta*Vt))+(Vd/Rb)+(-Vi/Rb)+(Vd/Ra)-xa + (Vd/Rd)+(-Vo/Rd);
    while (i < iter && abs(fVd) > thr){
        float der = ((2*Is/(eta*Vt)) * cosh(Vd/(eta*Vt))) + (1/Ra) + (1/Rb) + (1/Rd);
        float Vnew = Vd - fVd/der;
        Vd = Vnew;
        fVd = 2*Is*sinh(Vd/(eta*Vt))+(Vd/Rb)+(-Vi/Rb)+(Vd/Ra)-xa + (Vd/Rd)+(-Vo/Rd);
        i++;
    }
    float Vo = Vd/(Rd*Gg);
    xa = ((2.f/Ra) * Vd) - xa;
    
    return Vo;
}


void dplusClipper::prepare(float newFs){
    
    if (Fs != newFs){
        Fs = newFs;
        updateCoefficients();
    }
    
}

void dplusClipper::setKnob(float newOutput){
    
    if (outputpot != newOutput){
        outputpot = 0.00001f + 0.99998f * newOutput;
        updateCoefficients();
    }
    
}

void dplusClipper::updateCoefficients(){
    
     Rb = 10000.f;
     Ca = 1e-9;
     Ra = Ts/(2.f*Ca);
     Re = 10000.f * (1 - log10(1+9*(1-outputpot)));
     Rd = 10000.f - Re;
     Gg = (1.f/Rd) + (1.f/Re);
    
    
}
