#include <cstdlib>
#include "oscillator.h"
#include "constants.h"

float oscillator(const float f_freq, const float f_time, const Osc_t e_osc,
    const float f_lfo_hertz, const float f_lfo_amplitude) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator e_osc
    at a given moment, given its frequency and LFO characteristics.*/

    // Initialization
    float dOutput = 0.0;

    // Frequency oscillation times time
    float dW_T = f_freq * 2.0 * M_PI * f_time +
        f_lfo_amplitude * f_freq * (sin(f_lfo_hertz * 2.0 * M_PI * f_time));

    switch (e_osc) {
    case OSC_SINE:
        dOutput = sin(dW_T);
        break;

    case OSC_SQUARE:
        dOutput = sin(dW_T) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        dOutput = asin(sin(dW_T)) * M_2_PI;
        break;

    case OSC_SAW_DIG:  // summation of Fourier harmonics
        dOutput = 0.0;

        for (int n = 1; n < k_si_n_sawdig_harmonics; n++)
            dOutput += (sin(n * f_freq * 2.0 * M_PI * f_time)) / ((float) n);

        dOutput = dOutput * M_2_PI;
        break;

    case OSC_SAW:  // computation of sawtooth signal arithmetically
        dOutput = M_2_PI * (f_freq * M_PI * fmod(f_time, 1.0 / f_freq) - M_PI_2);
        break;

    case OSC_NOISE:
        return 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
        break;

    default:
        dOutput = 0.0;
    }

    return dOutput;
}

