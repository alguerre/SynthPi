#ifndef _INSTRUMENTS_h
#define _INSTRUMENTS_h

#include <iostream>
#include <string>
#include "envelopeADSR.h"
#include "constants.h"


class Instrument{

    protected:
        EnvelopeADSR obEnvelope;
        std::string sLabel;
        Instrument_t eInstrumentId;

    public:
        Instrument(std::string="Instrument");
        ~Instrument();

        virtual double Play(double, double) = 0; 
        static Instrument *Create(Instrument_t eDefaultInstrument = INS_NONE);
        void NoteOn(double);
        void NoteOff(double);
        std::string GetInstrumentLabel();
};


// Client class
class ChooseInstrument {
    public:
        ChooseInstrument(Instrument_t eDefaultInstrument = INS_NONE);
        ~ChooseInstrument();
        Instrument * GetInstrument();
        Instrument_t GetInstrumentId();

    private:
        Instrument * pobInstrument;
        Instrument_t eInstrumentId;
};

#endif