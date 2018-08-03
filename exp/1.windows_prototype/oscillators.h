#pragma once

#ifndef _SOUND_EFFECTS_h
#define _SOUND_EFFECTS_h

typedef enum {
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW_ANA,
    OSC_SAW_DIG
} Osc_t;

double oscillator(double dFreq, double dTime, Osc_t eType, double dLFOAmplitude = 0.0, double dLFOHertz = 0.0, int iArmonics = 50);

#endif
