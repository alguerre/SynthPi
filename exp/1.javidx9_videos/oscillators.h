#pragma once

#ifndef _SOUND_EFFECTS_h
#define _SOUND_EFFECTS_h

// General purpose oscillator
#define OSC_SINE 0
#define OSC_SQUARE 1
#define OSC_TRIANGLE 2
#define OSC_SAW_ANA 3
#define OSC_SAW_DIG 4

double oscillator(double dFreq, double dTime, int nType);

#endif
