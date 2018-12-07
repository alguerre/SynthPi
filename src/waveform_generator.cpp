#include "waveform_generator.h"

// Measurements structure initialization
WaveformGenerator::WaveformGenerator() {
  // Initialize configuration
  this->st_waveform_config.si_volume = 0.0;
  for (int i = 0; i < k_n_oscillators; i++) {
    this->st_waveform_config.e_oscillator[i] = OSC_SINE;
    this->st_waveform_config.si_octave[i] = 1;
  }
  this->st_waveform_config.si_lfo = 0.0;
  this->st_waveform_config.si_attack_time = 0.0;
  this->st_waveform_config.si_decay_time = 0.0;
  this->st_waveform_config.si_sustain_level = 0.0;
  this->st_waveform_config.si_release_time = 0.0;

  // Initialize waveform vectors
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++) {
    for (int j = 0; j < k_n_oscillators; j++) {
      this->pv_oscillator_wave[i].push_back(0.0);
      this->v_envelope.push_back(0.0);
      this->v_mix_output.push_back(0.0);
    }
  }
}


void WaveformGenerator::SetConfiguration(Meas_t st_measurements) {
  this->st_waveform_config = st_measurements;
}


double WaveformGenerator::Oscillator(double d_freq, double d_time, Osc_t eType) {
  /* OSCILLATOR returns the the amplitude of the specified oscillator eType
  at a given moment given its frequency.*/

  // Initialization
  double d_output = 0.0;

  // Frequency oscillation times time
  double d_w_t = d_freq * 2.0 * M_PI * d_time;

  // Oscillator definitions
  switch (eType) {
  case OSC_SINE:
    d_output = sin(d_w_t);
    break;

  case OSC_SQUARE:
    d_output = sin(d_w_t) > 0 ? 1.0 : -1.0;
    break;

  case OSC_TRIANGLE:
    d_output = asin(sin(d_w_t)) * M_2_PI;
    break;

  case OSC_SAW:
    d_output = M_2_PI * (d_freq * M_PI * fmod(d_time, 1.0 / d_freq) - M_PI_2);
    break;

  case OSC_NOISE:
    d_output = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
    break;

  default:
    d_output = 0.0;
  }

  return d_output;
}


void WaveformGenerator::CreateOscillators(double d_freq, double d_time, int si_oscillator_idx) {
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++) {
    this->pv_oscillator_wave[si_oscillator_idx].at(i) = 
      this->Oscillator(d_freq, d_time, this->st_waveform_config.e_oscillator[si_oscillator_idx]);
    d_time += d_time_elapsed;
  }
    
}


void WaveformGenerator::CreateEnvelope() {
}


std::vector<double> WaveformGenerator::CreateWaveform() {
  
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++){
  this->v_mix_output.at(i) = 0.0;
    for (int j = 0; j < k_n_oscillators; j++) {
      this->v_mix_output.at(i) += pv_oscillator_wave[j].at(i);
    }
  }
  return v_mix_output;
}


WaveformGenerator::~WaveformGenerator() {}
