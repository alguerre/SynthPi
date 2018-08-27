#ifndef HIHAT_H
#define HIHAT_H

#include <string>
#include "../instrument.h"
#include "../EnvelopeADSR.h"
#include "../oscillators.h"
#include "../constants.h"

// Envelope definition
#define HIHAT_STARTAMPLITUDE 1.00
#define HIHAT_ATTACKTIME     0.10
#define HIHAT_DECAYTIME      0.05
#define HIHAT_SUSTAINLEVEL   0.001
#define HIHAT_RELEASETIME    0.001
#define HIHAT_TAG            "drum_hihat"

// Instrument definition
class DrumHiHat : public Instrument{

    public:
        DrumHiHat(std::string="drum_hihat");

        double Play(double, double);

        ~DrumHiHat();
};
#endif
