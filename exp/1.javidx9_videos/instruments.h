#ifndef _INSTRUMENTS_h
#define _INSTRUMENTS_h

#include "EnvelopeADSR.h"

typedef enum {
    INS_BELL,
    INS_BELL8,
    INS_HARMONICA,
    INS_ORGAN,
    INS_DEBUG
} Instrument_t;

void update_envelope(Instrument_t eInstrument, EnvelopeADSR &oEnvelope);

double play_instrument(Instrument_t eInstrument, EnvelopeADSR oEnvelope, double dTime, double dFreq);

#endif