#include "bell8.h"


Bell8::Bell8(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        BELL8_STARTAMPLITUDE, 
        BELL8_ATTACKTIME, 
        BELL8_DECAYTIME, 
        BELL8_SUSTAINLEVEL, 
        BELL8_RELEASETIME, 
        BELL8_TAG);
}


double Bell8::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 1.00 * oscillator(dFreq * 2.0, dTime, OSC_SINE, 5.0, 0.001)
            + 0.50 * oscillator(dFreq * 4.0, dTime, OSC_SINE)
            + 0.25 * oscillator(dFreq * 8.0, dTime, OSC_SINE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

    return dOutput;
}


Bell8::~Bell8()
{
}
