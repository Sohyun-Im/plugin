/*
  ==============================================================================

    dplusOpamp.h
    Created: 2 Aug 2024 5:22:51pm
    Author:  Sohyun

  ==============================================================================
*/

#pragma once
#include <cmath>


class dplusOpamp{
public:
    
    float processSample(float Vi);
    
    void prepare(float newFs);
    
    void setKnob(float newOpamp);
    
private:
    
    void updateCoefficients();
    
    float Fs = 48000.f;
    float Ts = 1.f/Fs;
    
    float C1 = 10e-9;
    float R1 = Ts/(2.f*C1);

    float C2 = 47e-9;
    float R2 = Ts/(2.f*C2);
      
    float R3 = 10e3;
    float R4 = 1e6;
    float R5 = 4.7e3;
    float R8 = 1e6;
    
    float tonePot = 1.f;
    float k = 8.f;
    float R6 = (exp(-k * tonePot) - exp(-k)) / (1.f - exp(-k)) * 1000000.f;
    float Rn = R5 + R6;

    float Ga = 1.f + (R3/R1);
    float Gb = 1.f + (R2/Rn);
    float Gh = 1.f + (R4/(Gb*Rn));
    float Gx = (1.f/R8) + (1.f/(Ga*R1));

    float b0 = Gh/(Ga*R1*Gx);
    float b1 = ((R3/(Ga*R1))-1.f)*(Gh/Gx);
    float b2 = (-R2*R4)/(Gb*Rn);
    
    float x1 = 0.f;
    float x2 = 0.f;


    
};
