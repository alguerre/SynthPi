#ifndef _WAVEFORMGENERATOR_h
#define _WAVEFORMGENERATOR_h

#include <vector>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "constants.h"

class WaveformGenerator {

private:
  // Singleton: todo

  // Properties
  Meas_t st_waveform_config;
  const float f_time_elapsed = 1.0 / ((float)SND_PCM_RATE_STD);
  double f_time;
  std::vector<float> pv_oscillator_wave[2];
  std::vector<float> v_envelope;
  float pf_mix_output[SND_PCM_PERIOD_SIZE];

  // Methods
  void CreateEnvelope();
  float Oscillator(float, Osc_t);

public:

  // Constructor
  WaveformGenerator();

  // Methods
  void CreateOscillators(float, int);
  void SetConfiguration(Meas_t);
  float * CreateWaveform();
  Meas_t GetConfiguration();

  // Destructor
  ~WaveformGenerator();

};

#endif
