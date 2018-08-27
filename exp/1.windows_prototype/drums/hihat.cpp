#include "hihat.h"


DrumHiHat::DrumHiHat(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        HIHAT_STARTAMPLITUDE, 
        HIHAT_ATTACKTIME, 
        HIHAT_DECAYTIME, 
        HIHAT_SUSTAINLEVEL, 
        HIHAT_RELEASETIME, 
        HIHAT_TAG);
}


double DrumHiHat::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;
	double dDefaultVolume = 0.5;
	
    dOscillator = 0.10 * oscillator(FREQ_HIHAT, dTime, OSC_SQUARE, 1.5, 1.0)
                + 0.90 * oscillator(0, dTime, OSC_NOISE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator * dDefaultVolume;

   
    return dOutput;
}


DrumHiHat::~DrumHiHat()
{
}
