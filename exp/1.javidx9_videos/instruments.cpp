#define _USE_MATH_DEFINES  // this must be first to use cmath 
#include <cmath>
#include <iostream>
#include "instruments.h"
#include "oscillators.h"


void update_envelope(Instrument_t eInstrument, EnvelopeADSR &poEnvelope) {
    switch (eInstrument) {
    case INS_BELL:
        poEnvelope.Create(1.0, 0.01, 1.0, 0.0, 1.0);
        break;

    case INS_BELL8:
        poEnvelope.Create(1.0, 0.01, 0.5, 0.8, 0.1);
        break;

    case INS_HARMONICA:
        poEnvelope.Create(1.0, 0.05, 1.0, 0.95, 0.1);
        break;

    case INS_TEST:
        poEnvelope.Create(1.0, 0.10, 0.01, 0.8, 0.40);
        break;

    default:
        throw "Not valid instrument!";
    }
}


double play_instrument(Instrument_t eInstrument, EnvelopeADSR oEnvelope, double dTime, double dFreq){

    double dOutput = 0.0;

    switch (eInstrument) {
    case INS_BELL:
       dOutput = 1.0 * oscillator(dFreq, dTime, OSC_SINE, 5.0, 0.001)
            + 0.50 * oscillator(dFreq * 2, dTime, OSC_SINE)
            + 0.25 * oscillator(dFreq * 3, dTime, OSC_SINE);
        dOutput = dOutput * oEnvelope.GetAmplitude(dTime);
        break;

    case INS_BELL8:
        dOutput = 1.0 * oscillator(dFreq, dTime, OSC_SINE, 5.0, 0.001)
            + 0.50 * oscillator(dFreq * 2, dTime, OSC_SINE)
            + 0.25 * oscillator(dFreq * 3, dTime, OSC_SINE);
        dOutput = dOutput * oEnvelope.GetAmplitude(dTime);
        break;

    case INS_HARMONICA:
        dOutput =  1.0 * oscillator(dFreq, dTime, OSC_SQUARE, 5.0, 0.001)
            + 0.50 * oscillator(dFreq * 2, dTime, OSC_SQUARE);
        dOutput = dOutput * oEnvelope.GetAmplitude(dTime);
        break;

    case INS_TEST:
        dOutput = oscillator(dFreq, dTime, OSC_SINE);
        dOutput = dOutput * oEnvelope.GetAmplitude(dTime);
        break;

    default:
        std::cout << "Not valid instrument!" << std::endl;
    }

    return dOutput;
}
