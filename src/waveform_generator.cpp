#include "waveform_generator.h"
#include <iostream>

// Measurements structure initialization
WaveformGenerator::WaveformGenerator() {

  // Initialize configuration
  for (int i = 0; i < k_n_oscillators; i++) {
    this->pe_oscillator[i] = OSC_SINE;
    this->psi_octave[i] = 1;
  }

  this->f_volume = 0.0;
  this->f_lfo = 0.0;
  this->f_attack_time = 0.0;
  this->f_decay_time = 0.0;
  this->f_sustain_level = 0.0;
  this->f_release_time = 0.0;

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

  for (int i = 0; i < k_n_oscillators; i++) {
    pe_oscillator[i] = st_measurements.pe_oscillator[i];
    psi_octave[i] = st_measurements.psi_octave[i];
  }

  this->f_volume        = ((float) st_measurements.si_volume) / k_si_adc_max;
  this->f_lfo           = ((float) st_measurements.si_lfo) / k_si_adc_max;
  this->f_attack_time   = ((float) st_measurements.si_attack_time) / k_si_adc_max;
  this->f_decay_time    = ((float) st_measurements.si_decay_time) / k_si_adc_max;
  this->f_sustain_level = ((float) st_measurements.si_sustain_level) / k_si_adc_max;
  this->f_release_time  = ((float) st_measurements.si_release_time) / k_si_adc_max;
  std::cout << "f_volume = " << f_volume << std::endl;
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

  return f_output * this->f_volume;
}


void WaveformGenerator::CreateOscillators(float f_freq) {

  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++) {
    for (int j = 0; j < k_n_oscillators; j++) {
      this->pv_oscillator_wave[j].at(i) =
        this->Oscillator(f_freq, this->st_waveform_config.pe_oscillator[j]);
    }
    this->f_time += f_time_elapsed;
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
