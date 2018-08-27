#include "snare.h"


DrumSnare::DrumSnare(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        SNARE_STARTAMPLITUDE, 
        SNARE_ATTACKTIME, 
        SNARE_DECAYTIME, 
        SNARE_SUSTAINLEVEL, 
        SNARE_RELEASETIME, 
        SNARE_TAG);
}


double DrumSnare::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 0.50 * oscillator(FREQ_SNARE, dTime, OSC_SINE)
                + 0.50 * oscillator(0.0, dTime, OSC_NOISE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

   
    return dOutput;
}


DrumSnare::~DrumSnare()
{
}
