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
  const double d_time_elapsed = 1.0 / ((double)SND_PCM_RATE_STD);
  std::vector<double> pv_oscillator_wave[2];
  std::vector<double> v_envelope;
  std::vector<double> v_mix_output;

  // Methods
  void CreateOscillators(double, double, int);
  void CreateEnvelope();
  double Oscillator(double, double, Osc_t);

public:

  // Constructor
  WaveformGenerator();

  // Methods
  void SetConfiguration(Meas_t);
  std::vector<double> CreateWaveform();

  // Destructor
  ~WaveformGenerator();

};

#endif
