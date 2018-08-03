#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include "../instrument.h"
#include "../EnvelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define DEBUG_STARTAMPLITUDE 1.00
#define DEBUG_ATTACKTIME     0.01
#define DEBUG_DECAYTIME      1.00
#define DEBUG_SUSTAINLEVEL   0.90
#define DEBUG_RELEASETIME    1.00
#define DEBUG_TAG            "debug"

// Instrument definition
class Debug : public Instrument{

    public:
        Debug(std::string="debug");

        double Play(double, double);
        //EnvelopeADSR obEnvelope;

        ~Debug();
};
#endif
