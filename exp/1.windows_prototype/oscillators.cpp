#define _USE_MATH_DEFINES  // this must be first to use cmath 
#include <cmath>
#include <iostream>
#include "oscillators.h"


double oscillator(double dFreq, double dTime, Osc_t eType, double dLFOHertz, 
    double dLFOAmplitude,  int iArmonics) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator eType
    at a given moment, given its frequency and LFO characteristics.*/

    // Initialization
    double dOutput = 0.0;

    // Frequency oscillation times time
    double dW_T = dFreq * 2.0 * M_PI * dTime +
        dLFOAmplitude * dFreq * (sin(dFreq * 2.0 * M_PI * dTime)); 

    switch (eType) {
    case OSC_SINE:
        dOutput = sin(dW_T);
        break;

    case OSC_SQUARE:
        dOutput = sin(dW_T) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        dOutput = asin(sin(dW_T)) * M_2_PI;
        break;

    case OSC_SAW_ANA:  // summation of Fourier harmonics
        dOutput = 0.0;

        for (int n = 1; n < iArmonics; n++)
            dOutput += (sin(n * dFreq * 2.0 * M_PI * dTime)) / ((double) n);

        dOutput = dOutput * M_2_PI;
        break;

    case OSC_SAW_DIG:  // computation of sawtooth signal arithmetically
        dOutput = M_2_PI * (dFreq * M_PI * fmod(dTime, 1.0 / dFreq) - M_PI_2);
        break;

    case OSC_NOISE: 
        return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
        break;

    default:
        dOutput = 0.0;
    }

    return dOutput;
}
