#ifndef _TYPES_h

#define _TYPES_h

/* TYPES.H is aimed to allocate all the definitions of data types which will be 
 * part of dataflow the different components of the code. */

/* Oscillators */
typedef enum {
  OSC_NONE=0,
  OSC_SINE,
  OSC_SQUARE,
  OSC_TRIANGLE,
  OSC_SAW,
  OSC_SAW_DIG,
  OSC_NOISE
} Osc_t;


/* Measurements collects all the available variables whose value is set by a 
 * a external device such as potentiometer, dip, botton... */
typedef struct measurements {
  int si_volume;
  Osc_t pe_oscillator[2];
  int psi_octave[2];
  int si_lfo_amp;
  int si_lfo_freq;
  int si_attack_time;
  int si_decay_time;
  int si_sustain_level;
  int si_release_time;
} Meas_t;

/* Configuration collects the equivalencies between measurements and a
 * representative value for final algorithms. */
typedef struct configuration {
  float f_volume;
  Osc_t pe_oscillator[2];
  int psi_octave[2];
  float f_lfo_amp;
  float f_lfo_freq;
  float f_attack_time;
  float f_decay_time;
  float f_sustain_level;
  float f_release_time;
} Config_t;



#endif
