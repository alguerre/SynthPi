#ifndef BELL8_H
#define BELL8_H

#include <string>
#include "../instrument.h"
#include "../EnvelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define BELL8_STARTAMPLITUDE 1.00
#define BELL8_ATTACKTIME     0.01
#define BELL8_DECAYTIME      0.50
#define BELL8_SUSTAINLEVEL   0.90
#define BELL8_RELEASETIME    0.50
#define BELL8_TAG            "bell8"

// Instrument definition
class Bell8 : public Instrument{

    public:
        Bell8(std::string="bell8");

        double Play(double, double);
        //EnvelopeADSR obEnvelope;

        ~Bell8();
};
#endif
