/*
  ==============================================================================

    dplusClipper.h
    Created: 1 Aug 2024 11:02:54pm
    Author:  Sohyun

  ==============================================================================
*/

#pragma once
#include <cmath>

class dplusClipper{
public:
    //Callback functions
    float processSample(float Vi);
    
    void prepare(float newFs);
    
    void setKnob(float newOutput);
    
    
private:
    //Parameters
    
    const float eta = 2.0f;
    const float Is = 100e-9;
    const float Vt = 26e-3;
    
    float Fs = 48000.f;
    float Ts = 1.f/Fs;
    
    float Rb = 10000.f;
    float Ca = 1e-9;
    float Ra = Ts/(2.f*Ca);
    float outputpot = 1.f; //init
    float Re = 10000.f * (1 - log10(1+9*(1-outputpot)));
    float Rd = 10000.f - Re;
    
    float Gg = (1.f/Rd) + (1.f/Re);
    
    float xa = 0.f;
    
    float Vd = 0.f;
    float Vo = Vd/(Rd*Gg);
    int iter = 30;
    
    float thr = 0.000000001f;
    
    void updateCoefficients();
    
    
};
