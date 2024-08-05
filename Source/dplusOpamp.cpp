/*
  ==============================================================================

    dplusOpamp.cpp
    Created: 2 Aug 2024 5:22:51pm
    Author:  Sohyun

  ==============================================================================
*/

#include "dplusOpamp.h"

float dplusOpamp::processSample(float Vi){
    float Vo =  b0 * Vi + b1 * x1 + b2 * x2;

    float Vx = (1/Gh)*Vo + ((R2*R4)/(Gb*Gh*Rn))*x2;
    float VR1 = (Vi-Vx+(R3*x1))/Ga;

    float VRn = (Vx-(R2*x2))/Gb;
    float VR2 = (R2/Rn)*VRn + (R2*x2);
  
     x1 = (2/R1)*VR1 - x1;
     x2 = (2/R2)*VR2 - x2;
    
    return Vo;
}


void dplusOpamp::prepare(float newFs){
    if (Fs != newFs){
        Fs = newFs;
        updateCoefficients();
    }
    
}

void dplusOpamp::setKnob(float newOpamp){
    
    if (tonePot != newOpamp){
        tonePot = newOpamp;
        updateCoefficients();
    }
    
}

void dplusOpamp::updateCoefficients(){
    
     Ts = 1.f/Fs;
     R1 = Ts/(2.f*C1);
     R2 = Ts/(2.f*C2);
 
     R6 = (exp(-k * tonePot) - exp(-k)) / (1.f - exp(-k)) * 1000000.f;
     Rn = R5 + R6;

     Ga = 1.f + (R3/R1);
     Gb = 1.f + (R2/Rn);
     Gh = 1.f + (R4/(Gb*Rn));
     Gx = (1.f/R8) + (1.f/(Ga*R1));

     b0 = Gh/(Ga*R1*Gx);
     b1 = ((R3/(Ga*R1))-1.f)*(Gh/Gx);
     b2 = (-R2*R4)/(Gb*Rn);
    
  
}
