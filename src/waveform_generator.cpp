#include "waveform_generator.h"
#include <iostream>

// Measurements structure initialization
WaveformGenerator::WaveformGenerator() {

  // Initialize configuration
  for (int i = 0; i < k_si_n_oscillators; i++) {
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
    for (int j = 0; j < k_si_n_oscillators; j++) {
      this->pv_oscillator_wave[j].push_back(0.0);
    }
    this->v_envelope.push_back(0.0);
    this->pf_mix_output[i] = 0.0;
  }

  // Timing
  this->f_time = 0.0;
}


/*void WaveformGenerator::SetConfiguration(Meas_t st_measurements) {
  this->st_waveform_config = st_measurements;

  for (int i = 0; i < k_si_n_oscillators; i++) {
    pe_oscillator[i] = st_measurements.pe_oscillator[i];
    psi_octave[i] = st_measurements.psi_octave[i];
  }

  this->f_volume        = ((float) st_measurements.si_volume) / k_f_adc_max;
  this->f_lfo           = ((float) st_measurements.si_lfo) / k_f_adc_max;
  this->f_attack_time   = ((float) st_measurements.si_attack_time) / k_f_adc_max;
  this->f_decay_time    = ((float) st_measurements.si_decay_time) / k_f_adc_max;
  this->f_sustain_level = ((float) st_measurements.si_sustain_level) / k_f_adc_max;
  this->f_release_time  = ((float) st_measurements.si_release_time) / k_f_adc_max;
}
*/

/*Meas_t WaveformGenerator::GetConfiguration() {
  return this->st_waveform_config;
}*/


void WaveformGenerator::CreateEnvelope() {
}


float * WaveformGenerator::CreateWaveform() {
  
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++){
  this->pf_mix_output[i] = 0.0;
    for (int j = 0; j < k_si_n_oscillators; j++) {
      this->pf_mix_output[i] += pv_oscillator_wave[j].at(i);
    }
  }
  
  return this->pf_mix_output;
}


WaveformGenerator::~WaveformGenerator() {
}
