#ifndef _TYPES_h

#define _TYPES_h

/* TYPES.H is aimed to allocate all the definitions of data types which will be 
 * part of dataflow the different components of the code. */

/* Oscillators */
typedef enum {
  OSC_SINE=0,
  OSC_SQUARE,
  OSC_TRIANGLE,
  OSC_SAW,
  OSC_NOISE
} Osc_t;


/* Measurements collects all the available variables whose value is set by a 
 * a external device such as potentiometer, dip, botton... */
typedef struct measurements {
  int si_volume;
  Osc_t e_oscillator[2];
  int si_octave[2];
  int si_lfo;
  int si_attack_time;
  int si_decay_time;
  int si_sustain_level;
  int si_release_time;
} Meas_t;


#endif
