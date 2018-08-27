#ifndef BELL_H
#define BELL_H

#include <string>
#include "../instrument.h"
#include "../envelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define BELL_STARTAMPLITUDE 1.00
#define BELL_ATTACKTIME     0.01
#define BELL_DECAYTIME      1.00
#define BELL_SUSTAINLEVEL   0.90
#define BELL_RELEASETIME    1.00
#define BELL_TAG            "bell"

// Instrument definition
class Bell : public Instrument{

    public:
        Bell(std::string="bell");

        double Play(double, double);
        //EnvelopeADSR obEnvelope;

        ~Bell();
};
#endif
