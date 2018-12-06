#include "measurements.h"

Measurements::Measurements() {
  // Measurements structure initialization
  this->st_measurements.si_volume = 0.0;
  this->st_measurements.e_oscillator_one = OSC_SINE;
  this->st_measurements.e_oscillator_two = OSC_SINE;
  this->st_measurements.si_octave_one = 1;
  this->st_measurements.si_octave_two = 1;
  this->st_measurements.si_lfo = 0.0;
  this->st_measurements.si_attack_time = 0.0;
  this->st_measurements.si_decay_time = 0.0;
  this->st_measurements.si_sustain_level = 0.0;
  this->st_measurements.si_release_time = 0.0;
}


void Measurements::ConfigureOscillators() {
  this->st_measurements.si_lfo =
      this->pob_spi->AnalogRead(k_pot_lfo);
}


void Measurements::ConfigureADSR() {
  this->st_measurements.si_attack_time =
      this->pob_spi->AnalogRead(k_pot_attack_time);

  this->st_measurements.si_decay_time =
      this->pob_spi->AnalogRead(k_pot_decay_time);

  this->st_measurements.si_sustain_level =
      this->pob_spi->AnalogRead(k_pot_sustain_time);

  this->st_measurements.si_release_time =
      this->pob_spi->AnalogRead(k_pot_release_time);
}


void Measurements::ChangeVolume() {
  this->st_measurements.si_volume =
      this->pob_spi->AnalogRead(k_pot_volume);
}


Meas_t Measurements::GetMeasurements() {
  this->ConfigureOscillators();
  this->ConfigureADSR();
  this->ChangeVolume();
  return this->st_measurements;
}


/*Measurements* Measurements::get_instance() {
    if (pobMeasurements == NULL)
        pobMeasurements = new Measurements();
    else
        std::cout << "Singleton error" << std::endl;

    return pobMeasurements;
}*/

void Measurements::Print() {
  std::cout <<
      "Volume:           " << this->st_measurements.si_volume <<
      "\nOscillator one: " << this->st_measurements.e_oscillator_one <<
      "\nOscillator two: " << this->st_measurements.e_oscillator_two <<
      "\nOctave one:     " << this->st_measurements.si_octave_one <<
      "\nOctave two:     " << this->st_measurements.si_octave_two <<
      "\nLFO:            " << this->st_measurements.si_lfo <<
      "\nAttack Time:    " << this->st_measurements.si_attack_time <<
      "\nDecay Time:     " << this->st_measurements.si_decay_time <<
      "\nSustain Level:  " << this->st_measurements.si_sustain_level <<
      "\nRelease Time:   " << this->st_measurements.si_release_time <<
      std::endl;
}

// Destructor
Measurements::~Measurements() {
}
