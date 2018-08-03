#ifndef _INSTRUMENTS_h
#define _INSTRUMENTS_h

#include <iostream>
#include <string>
#include "EnvelopeADSR.h"
#include "constants.h"


class Instrument{

    public:
        Instrument(std::string="Instrument");

        virtual double Play(double, double) = 0; 
        static Instrument *Create();

        std::string sLabel;   
        EnvelopeADSR obEnvelope;

        ~Instrument();

};


// Client class
class ChooseInstrument {
    public:
        ChooseInstrument();
        ~ChooseInstrument();
        Instrument* getInstrument();

    private:
        Instrument * pobInstrument;
};

#endif