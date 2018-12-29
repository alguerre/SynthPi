#include "waveform_generator.h"
#include <iostream>

// Measurements structure initialization
WaveformGenerator::WaveformGenerator() {
  // Initialize configuration
  this->st_waveform_config.si_volume = 0.0;
  for (int i = 0; i < k_n_oscillators; i++) {
    this->st_waveform_config.pe_oscillator[i] = OSC_SINE;
    this->st_waveform_config.psi_octave[i] = 1;
  }
  this->st_waveform_config.si_lfo = 0.0;
  this->st_waveform_config.si_attack_time = 0.0;
  this->st_waveform_config.si_decay_time = 0.0;
  this->st_waveform_config.si_sustain_level = 0.0;
  this->st_waveform_config.si_release_time = 0.0;

  // Initialize waveform vectors
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++) {
    for (int j = 0; j < k_n_oscillators; j++) {
      this->pv_oscillator_wave[j].push_back(0.0);
    }
    this->v_envelope.push_back(0.0);
    this->pf_mix_output[i] = 0.0;
  }

  // Timing
  this->f_time = 0.0;
}


void WaveformGenerator::SetConfiguration(Meas_t st_measurements) {
  this->st_waveform_config = st_measurements;
}


Meas_t WaveformGenerator::GetConfiguration() {
  return this->st_waveform_config;
}


float WaveformGenerator::Oscillator(float f_freq, Osc_t eType) {
  /* OSCILLATOR returns the the amplitude of the specified oscillator eType
  at a given moment given its frequency.*/

  // Initialization
  float f_output = 0.0;

  // Frequency oscillation times time
  float f_w_t = f_freq * 2.0 * M_PI * this->f_time;

  // Oscillator definitions
  switch (eType) {
  case OSC_SINE:
    f_output = sin(f_w_t);
    break;

  case OSC_SQUARE:
    f_output = sin(f_w_t) > 0 ? 1.0 : -1.0;
    break;

  case OSC_TRIANGLE:
    f_output = asin(sin(f_w_t)) * M_2_PI;
    break;

  case OSC_SAW:
    f_output = M_2_PI * (f_freq * M_PI * fmod(this->f_time, 1.0 / f_freq) - M_PI_2);
    break;

  case OSC_NOISE:
    f_output = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
    break;

  default:
    f_output = 0.0;
  }

  return f_output;
}


void WaveformGenerator::CreateOscillators(float f_freq, int si_oscillator_idx) {

  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++) {
    this->pv_oscillator_wave[si_oscillator_idx].at(i) = 
      this->Oscillator(f_freq, this->st_waveform_config.pe_oscillator[si_oscillator_idx]);
    this->f_time += f_time_elapsed;
    //std::cout << d_time << std::endl;
  }
    
}


void WaveformGenerator::CreateEnvelope() {
}


float * WaveformGenerator::CreateWaveform() {
  
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++){
  this->pf_mix_output[i] = 0.0;
    for (int j = 0; j < k_n_oscillators; j++) {
      this->pf_mix_output[i] += pv_oscillator_wave[j].at(i);
    }
  }
  
  return this->pf_mix_output;
}


WaveformGenerator::~WaveformGenerator() {
}
