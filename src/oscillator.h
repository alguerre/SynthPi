#ifndef _OSCILLATOR_h
#define _OSCILLATOR_h

#include "types.h"

float oscillator(const float f_freq,
    const float f_time,
    const Osc_t e_osc,
    const float f_lfo_hertz,
    const float f_lfo_amplitude);

#endif
