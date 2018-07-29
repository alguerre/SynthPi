#include "debug.h"


Debug::Debug(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        DEBUG_STARTAMPLITUDE, 
        DEBUG_ATTACKTIME, 
        DEBUG_DECAYTIME, 
        DEBUG_SUSTAINLEVEL, 
        DEBUG_RELEASETIME, 
        DEBUG_TAG);
    this->obEnvelope.Print();
}


double Debug::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 1.00 * oscillator(dFreq, dTime, OSC_SINE);
	
    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

    return dOutput;
}


Debug::~Debug()
{
}
