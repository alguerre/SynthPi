#ifndef HARMONICA_H
#define HARMONICA_H

#include <string>
#include "../instruments.h"
#include "../EnvelopeADSR.h"
#include "../oscillators.h"

// Envelope definition
#define HARMONICA_STARTAMPLITUDE 1.00
#define HARMONICA_ATTACKTIME     0.05
#define HARMONICA_DECAYTIME      1.00
#define HARMONICA_SUSTAINLEVEL   0.95
#define HARMONICA_RELEASETIME    0.10
#define HARMONICA_TAG            "harmonica"

// Instrument definition
class Harmonica : public Instrument{

    public:
        Harmonica(std::string="harmonica");

        double Play(double, double);

        ~Harmonica();
};
#endif
