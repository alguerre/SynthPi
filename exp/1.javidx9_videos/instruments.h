#ifndef _INSTRUMENTS_h
#define _INSTRUMENTS_h

#include <string>
#include "EnvelopeADSR.h"

class Instrument{

    public:
        Instrument(std::string="Instrument");

        virtual double Play(double, double) = 0; 
        std::string sLabel;   
        EnvelopeADSR obEnvelope;

        ~Instrument();

};

#endif