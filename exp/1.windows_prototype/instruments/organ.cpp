#include "organ.h"


Organ::Organ(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        ORGAN_STARTAMPLITUDE, 
        ORGAN_ATTACKTIME, 
        ORGAN_DECAYTIME, 
        ORGAN_SUSTAINLEVEL, 
        ORGAN_RELEASETIME, 
        ORGAN_TAG);
}


double Organ::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 1.00 * oscillator(dFreq, dTime, OSC_SINE)
                + 1.00 * oscillator(dFreq, dTime, OSC_SAW_ANA);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

   
    return dOutput;
}


Organ::~Organ()
{
}
