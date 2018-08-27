#ifndef KICK_H
#define KICK_H

#include <string>
#include "../instrument.h"
#include "../EnvelopeADSR.h"
#include "../oscillators.h"
#include "../constants.h"

// Envelope definition
#define KICK_STARTAMPLITUDE 1.00
#define KICK_ATTACKTIME     0.01
#define KICK_DECAYTIME      0.15
#define KICK_SUSTAINLEVEL   0.0001
#define KICK_RELEASETIME    0.0001
#define KICK_TAG            "drum_kick"
#define DRUM_FREQUENCY       322.54

// Instrument definition
class DrumKick : public Instrument{

    public:
        DrumKick(std::string="drum_kick");

        double Play(double, double);

        ~DrumKick();
};
#endif
