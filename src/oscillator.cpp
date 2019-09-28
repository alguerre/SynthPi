#include <cstdlib>
#include "oscillator.h"
#include "constants.h"

// Constructor
Oscillator::Oscillator(){
}


float Oscillator::GenerateOscillation(const float f_freq, const float f_time,
    const Config_t st_config, const int si_osc_index){
    //const Osc_t e_osc, const float f_lfo_freq, const float f_lfo_amplitude) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator e_osc
    at a given moment, given its frequency and LFO characteristics.*/

    // Initialization
    float f_output = 0.0;
    float f_lfo_amplitude = st_config.f_lfo_amp;
    float f_lfo_freq = st_config.f_lfo_freq;
    Osc_t e_osc = st_config.pe_oscillator[si_osc_index];
    int si_octave = st_config.psi_octave[si_osc_index];

    // Frequency oscillation times time
    float f_wt = f_freq * si_octave * 2.0 * M_PI * f_time +
        LowFrequencyOscillator(f_freq, f_time, f_lfo_amplitude, f_lfo_freq);

    switch (e_osc) {
    case OSC_SINE:
        f_output = sin(f_wt);
        break;

    case OSC_SQUARE:
        f_output = sin(f_wt) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        f_output = asin(sin(f_wt)) * M_2_PI;
        break;

    case OSC_SAW_DIG:  // summation of Fourier harmonics
        f_output = 0.0;

        for (int n = 1; n < k_si_n_sawdig_harmonics; n++)
            f_output += (sin(n * f_freq * 2.0 * M_PI * f_time)) / ((float) n);

        f_output = f_output * M_2_PI;
        break;

    case OSC_SAW:  // computation of sawtooth signal arithmetically
        f_output = M_2_PI *
          (f_freq * M_PI * fmod(f_time, 1.0 / f_freq) - M_PI_2);
        break;

    case OSC_NOISE:
        return 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
        break;

    default:
        f_output = 0.0;
    }

    // Not generate data for low frequencies
    if (f_freq < k_f_min_freq){
      f_output = 0.0;
    }

    return f_output;
}


float Oscillator::LowFrequencyOscillator(const float f_freq, const float f_time,
    const float f_lfo_amplitude, const float f_lfo_freq){
  return f_lfo_amplitude * f_freq * (sin(f_lfo_freq * 2.0 * M_PI * f_time));
}


// Destructor
Oscillator::~Oscillator(){
}
