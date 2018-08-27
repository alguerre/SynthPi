#include "kick.h"


DrumKick::DrumKick(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
		KICK_STARTAMPLITUDE,
		KICK_ATTACKTIME,
		KICK_DECAYTIME,
		KICK_SUSTAINLEVEL,
		KICK_RELEASETIME,
		KICK_TAG);
}


double DrumKick::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator = 2.0 * oscillator(FREQ_KICK, dTime, OSC_SINE)
                + 0.02 * oscillator(0, dTime, OSC_NOISE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

   
    return dOutput;
}


DrumKick::~DrumKick()
{
}
