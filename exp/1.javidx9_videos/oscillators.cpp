#define _USE_MATH_DEFINES  // this must be first to use cmath 
#include <cmath>
#include <iostream>
#include "oscillators.h"


double oscillator(double dFreq, double dTime, int nType) {

    double dOutput = 0.0;

    switch (nType) {
    case OSC_SINE:
        dOutput = sin(dFreq * 2.0 * M_PI * dTime);
        break;

    case OSC_SQUARE:
        dOutput = sin(dFreq * 2.0 * M_PI * dTime) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        dOutput = asin(sin(dFreq * 2.0 * M_PI * dTime)) * M_2_PI;
        break;

    case OSC_SAW_ANA:  // summation of Fourier harmonics
        dOutput = 0.0;

        for (double n = 1.0; n < 40.0; n++)
            dOutput += (sin(n * dFreq * 2.0 * M_PI * dTime)) / n;

        dOutput = dOutput * M_2_PI;
        break;

    case OSC_SAW_DIG:  // computation of sawtooth signal arithmetically
        dOutput = M_2_PI * (dFreq * M_PI * fmod(dTime, 1.0 / dFreq) - M_PI_2);
        break;

    default:
        dOutput = 0.0;
    }

    return dOutput;
}
