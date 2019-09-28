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

  // Configuration
  float f_volume;
  Osc_t pe_oscillator[2];
  float psi_octave[2];
  float f_lfo;
  float f_attack_time;
  float f_decay_time;
  float f_sustain_level;
  float f_release_time;

  // Methods
  void CreateEnvelope();

public:

  // Constructor
  WaveformGenerator();

  // Methods
  //void SetConfiguration(Meas_t);
  float * CreateWaveform();
  //Meas_t GetConfiguration();

  // Destructor
  ~WaveformGenerator();

};

#endif
