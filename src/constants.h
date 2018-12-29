#ifndef _CONSTANTS_h

#define _CONSTANTS_h

/* CONSTANTS.H is aimed to allocate all the configurable variables whose value 
 * is not changed by any function or method. It can be understood as a 
 * configuration file. */

// Spi configuration
const int k_spi_speed = 1000000;
const int k_spi_channel = 0;
const int k_spi_max_channel = 10;
const int k_si_default_spi_channel = 0;

// Spi channel for potentiometers
const int k_pot_volume = 5;
const int k_pot_lfo = 4;
const int k_pot_attack_time = 3;
const int k_pot_decay_time = 2;
const int k_pot_sustain_time = 1;
const int k_pot_release_time = 0;

// Oscillators
const int k_n_oscillators = 2;
const int k_gpio_oscillator_m[2] = {25, 23};
const int k_gpio_oscillator_l[2] = {24, 22};

// Keys
const int k_n_keys = 6;
const int pk_keys[6] = {29, 28, 27, 26, 21, 3};

// ALSA configuration
#define ALSA_PCM_NEW_HW_PARAMS_AP
#define SND_PCM_RATE_STD (44100)
#define SND_PCM_CHANNEL_MONO (1)
#define SND_PCM_CHANNEL_STEREO (2)
#define SND_PCM_PERIOD_SIZE (4) 
#define SND_PCM_SOFT_RESAMPLE (1)
#define SND_PCM_LATENCY (500000)

#endif
