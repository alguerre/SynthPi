#ifndef _TYPES_h

#define _TYPES_h

/* Oscillators */
typedef enum {
  OSC_SINE=0,
  OSC_SQUARE,
  OSC_TRIANGLE,
  OSC_SAW,
  OSC_NOISE
} Osc_t;

typedef struct measurements {
  double si_volume;
  Osc_t e_oscillator_one;
  Osc_t e_oscillator_two;
  int si_octave_one;
  int si_octave_two;
  int si_lfo;
  int si_attack_time;
  int si_decay_time;
  int si_sustain_level;
  int si_release_time;
} Meas_t;


#endif
