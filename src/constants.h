#ifndef _CONSTANTS_h

#define _CONSTANTS_h

#include <math.h>

/* CONSTANTS.H is aimed to allocate all the configurable variables whose value 
 * is not changed by any function or method. It can be understood as a 
 * configuration file. */

// ADC
const int k_si_adc_bits = 10;
const float k_f_r1 = 10e+3;
const float k_f_r2 = 1e+3;
const float k_f_adc_max = (pow(2.0, k_si_adc_bits) - 1) *
  (k_f_r1) / (k_f_r1 + k_f_r2);

// Spi configuration
const int k_si_spi_speed = 1000000;
const int k_si_spi_channel = 0;
const int k_si_spi_max_channel = 10;
const int k_si_default_spi_channel = 0;

// Spi channel for potentiometers
const int k_si_pot_volume = 5;
const int k_si_pot_lfo_amp = 4;
const int k_si_pot_lfo_freq = 3; // spare
const int k_si_pot_attack_time = 3;
const int k_si_pot_decay_time = 2;
const int k_si_pot_sustain_time = 1;
const int k_si_pot_release_time = 0;

// Oscillators
const int k_si_n_oscillators = 2;
const int k_psi_gpio_oscillator_m[2] = {25, 23};
const int k_psi_gpio_oscillator_l[2] = {24, 22};
const int k_psi_gpio_octave_m[2] = {23, 23};
const int k_psi_gpio_octave_l[2] = {22, 22};
const float k_f_min_freq = 110.0;
const int k_si_n_sawdig_harmonics = 10;
const float k_f_base_freq = 220.0;
const float k_f_freq_note_interval = pow(2.0, 1.0 / 12.0);
const float k_f_lfo_max_amp = 25.0;

// Keys
const int k_si_n_keys = 6;
const int k_psi_keys[6] = {29, 28, 27, 26, 21, 3};

// ALSA configuration
#define ALSA_PCM_NEW_HW_PARAMS_AP
#define SND_PCM_RATE_STD (44100)
#define SND_PCM_CHANNEL_MONO (1)
#define SND_PCM_CHANNEL_STEREO (2)
#define SND_PCM_PERIOD_SIZE (4) 
#define SND_PCM_SOFT_RESAMPLE (1)
#define SND_PCM_LATENCY (500000)

// ADSR
const float k_f_minimum_amplitude_adsr = (float) 0.001;


#endif
