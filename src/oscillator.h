#ifndef _OSCILLATOR_h
#define _OSCILLATOR_h

#include "types.h"

class Oscillator {
/* OSCILLATOR generates a oscillating signal using different waveforms (sine,
 * square, ...). Different effects, such as LFO, can be included. */


private:

  // Methods
  float LowFrequencyOscillator(
      const float,
      const float,
      const float,
      const float);

public:

  // Constructor
  Oscillator();

  // Methods
  float GenerateOscillation(
      const float,
      const float,
      const Config_t,
      const int);

  // Destructor
  ~Oscillator();

};


#endif
