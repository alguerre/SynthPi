#ifndef ORGAN_H
#define ORGAN_H

#include <string>
#include "../instrument.h"
#include "../envelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define ORGAN_STARTAMPLITUDE 1.00
#define ORGAN_ATTACKTIME     0.10
#define ORGAN_DECAYTIME      0.01
#define ORGAN_SUSTAINLEVEL   0.80
#define ORGAN_RELEASETIME    0.20
#define ORGAN_TAG            "organ"

// Instrument definition
class Organ : public Instrument{

    public:
        Organ(std::string="organ");

        double Play(double, double);

        ~Organ();
};
#endif
