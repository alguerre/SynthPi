#include "configuration.h"


Configuration::Configuration() {
  // Measurements structure initialization
  this->st_configuration.f_volume = 0.0;
  for (int i = 0; i < k_si_n_oscillators; i++) {
    this->st_configuration.pe_oscillator[i] = OSC_SINE;
    this->st_configuration.psi_octave[i] = 1;
  }
  this->st_configuration.f_lfo = 0.0;
  this->st_configuration.f_attack_time = 0.0;
  this->st_configuration.f_decay_time = 0.0;
  this->st_configuration.f_sustain_level = 0.0;
  this->st_configuration.f_release_time = 0.0;
}


void Configuration::ConfigureOscillators(Meas_t st_meas){
  this->st_configuration.f_lfo = st_meas.si_lfo / k_f_adc_max;
}


void Configuration::ConfigureADSR(Meas_t st_meas){
  /* TODO: it is needed to provide the proper range, 0 to 1 may be not be
  proper */

  this->st_configuration.f_attack_time = st_meas.si_attack_time / k_f_adc_max;

  this->st_configuration.f_decay_time = st_meas.si_decay_time / k_f_adc_max;

  this->st_configuration.f_sustain_level =
      st_meas.si_sustain_level / k_f_adc_max;

  this->st_configuration.f_release_time = st_meas.si_release_time / k_f_adc_max;

}


void Configuration::ConfigureVolume(Meas_t st_meas){
  this->st_configuration.f_volume = ((float) st_meas.si_volume) / k_f_adc_max;
}


Config_t Configuration::GetConfiguration(Meas_t st_meas) {
  this->ConfigureOscillators(st_meas);
  this->ConfigureADSR(st_meas);
  this->ConfigureVolume(st_meas);
  return this->st_configuration;
}


std::ostream& operator << (std::ostream& cout, const Configuration& ob_config)
{
  return std::cout <<
    "\nCONFIGURATION     " <<
    "\n================" <<
    "\nVolume:         " << ob_config.st_configuration.f_volume <<
    "\nOscillator one: " << ob_config.st_configuration.pe_oscillator[0] <<
    "\nOscillator two: " << ob_config.st_configuration.pe_oscillator[1] <<
    "\nOctave one:     " << ob_config.st_configuration.psi_octave[0] <<
    "\nOctave two:     " << ob_config.st_configuration.psi_octave[1] <<
    "\nLFO:            " << ob_config.st_configuration.f_lfo <<
    "\nAttack Time:    " << ob_config.st_configuration.f_attack_time <<
    "\nDecay Time:     " << ob_config.st_configuration.f_decay_time <<
    "\nSustain Level:  " << ob_config.st_configuration.f_sustain_level <<
    "\nRelease Time:   " << ob_config.st_configuration.f_release_time <<
    "\n";

}


// Destructor
Configuration::~Configuration() {
}
