#include "bell.h"


Bell::Bell(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        BELL_STARTAMPLITUDE, 
        BELL_ATTACKTIME, 
        BELL_DECAYTIME, 
        BELL_SUSTAINLEVEL, 
        BELL_RELEASETIME, 
        BELL_TAG);
}


double Bell::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 1.00 * oscillator(dFreq, dTime, OSC_SINE, 5.0, 0.001)
               + 0.50 * oscillator(dFreq * 2.0, dTime, OSC_SINE)
               + 0.25 * oscillator(dFreq * 4.0, dTime, OSC_SINE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

   
    return dOutput;
}


Bell::~Bell()
{
}
