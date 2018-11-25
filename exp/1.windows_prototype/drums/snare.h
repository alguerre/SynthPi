#ifndef SNARE_H
#define SNARE_H

#include <string>
#include "../instrument.h"
#include "../envelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define SNARE_STARTAMPLITUDE 1.00
#define SNARE_ATTACKTIME     0.00
#define SNARE_DECAYTIME      0.20
#define SNARE_SUSTAINLEVEL   0.001
#define SNARE_RELEASETIME    0.001
#define SNARE_TAG            "drum_snare"

// Instrument definition
class DrumSnare : public Instrument{

    public:
        DrumSnare(std::string="drum_snare");

        double Play(double, double);

        ~DrumSnare();
};
#endif
