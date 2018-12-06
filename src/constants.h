#ifndef _CONSTANTS_h

#define _CONSTANTS_h

// Spi configuration
const int k_spi_speed = 1000000;
const int k_spi_channel = 0;

// Spi channel for potentiometers
const int k_pot_volume = 5;
const int k_pot_lfo = 4;
const int k_pot_attack_time = 3;
const int k_pot_decay_time = 2;
const int k_pot_sustain_time = 1;
const int k_pot_release_time = 0;

// Oscillators
const int k_gpio_oscillator_one_m = 25;
const int k_gpio_oscillator_one_l = 24;
const int k_gpio_oscillator_two_m = 23;
const int k_gpio_oscillator_two_l = 22;

// Keys
const int pk_keys[6] = {29, 28, 27, 26, 21, 3};

#endif
