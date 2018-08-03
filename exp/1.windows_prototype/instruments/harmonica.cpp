#include "harmonica.h"


Harmonica::Harmonica(std::string sLabel):Instrument(sLabel){
    this->obEnvelope.Create(
        HARMONICA_STARTAMPLITUDE, 
        HARMONICA_ATTACKTIME, 
        HARMONICA_DECAYTIME, 
        HARMONICA_SUSTAINLEVEL, 
        HARMONICA_RELEASETIME, 
        HARMONICA_TAG);
    this->obEnvelope.Print();
}


double Harmonica::Play(double dTime, double dFreq) {
    double dOscillator = 0.0;
    double dAmplitude = 0.0;
    double dOutput = 0.0;

    dOscillator =  1.00 * oscillator(dFreq, dTime, OSC_SQUARE, 5.0, 0.001)
                 + 0.50 * oscillator(dFreq * 2.0, dTime, OSC_SQUARE);

    dAmplitude = this->obEnvelope.GetAmplitude(dTime);

    dOutput = dAmplitude * dOscillator;

   
    return dOutput;
}


Harmonica::~Harmonica()
{
}
