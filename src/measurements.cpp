#include "measurements.h"

Measurements::Measurements() {
  // Measurements structure initialization
  this->st_measurements.si_volume = 0;
  for (int i = 0; i < k_si_n_oscillators; i++) {
    this->st_measurements.pe_oscillator[i] = OSC_SINE;
    this->st_measurements.psi_octave[i] = 1;
  }
  this->st_measurements.si_lfo = 0;
  this->st_measurements.si_attack_time = 0;
  this->st_measurements.si_decay_time = 0;
  this->st_measurements.si_sustain_level = 0;
  this->st_measurements.si_release_time = 0;
}


void Measurements::ConfigureOscillators() {

  for (int i = 0; i < k_si_n_oscillators; i++) {
    int si_oscillator = 2 * digitalRead(k_psi_gpio_oscillator_m[i]) +
      digitalRead(k_psi_gpio_oscillator_l[i]);

    switch (si_oscillator) {
    case 0:
      this->st_measurements.pe_oscillator[i] = OSC_SINE;
      break;
    case 1:
      this->st_measurements.pe_oscillator[i] = OSC_SQUARE;
      break;
    case 2:
      this->st_measurements.pe_oscillator[i] = OSC_TRIANGLE;
      break;
    case 3:
      this->st_measurements.pe_oscillator[i] = OSC_SAW;
      break;
    default:
      this->st_measurements.pe_oscillator[i] = OSC_SINE;
    }
  }
  
  this->st_measurements.si_lfo =
    this->pob_spi->AnalogRead(k_si_pot_lfo);
}


void Measurements::ConfigureADSR() {
  this->st_measurements.si_attack_time =
      this->pob_spi->AnalogRead(k_si_pot_attack_time);

  this->st_measurements.si_decay_time =
      this->pob_spi->AnalogRead(k_si_pot_decay_time);

  this->st_measurements.si_sustain_level =
      this->pob_spi->AnalogRead(k_si_pot_sustain_time);

  this->st_measurements.si_release_time =
      this->pob_spi->AnalogRead(k_si_pot_release_time);
}


void Measurements::ChangeVolume() {
  this->st_measurements.si_volume =
      this->pob_spi->AnalogRead(k_si_pot_volume);
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


std::ostream& operator << (std::ostream& cout, const Measurements& ob_meas)
{
	return std::cout <<
	  "\nMEASUREMENTS      " <<
	  "\n================" <<
		"\nVolume:           " << ob_meas.st_measurements.si_volume <<
		"\nOscillator one: " << ob_meas.st_measurements.pe_oscillator[0] <<
		"\nOscillator two: " << ob_meas.st_measurements.pe_oscillator[1] <<
		"\nOctave one:     " << ob_meas.st_measurements.psi_octave[0] <<
		"\nOctave two:     " << ob_meas.st_measurements.psi_octave[1] <<
		"\nLFO:            " << ob_meas.st_measurements.si_lfo <<
		"\nAttack Time:    " << ob_meas.st_measurements.si_attack_time <<
		"\nDecay Time:     " << ob_meas.st_measurements.si_decay_time <<
		"\nSustain Level:  " << ob_meas.st_measurements.si_sustain_level <<
		"\nRelease Time:   " << ob_meas.st_measurements.si_release_time <<
		"\n";

}


// Destructor
Measurements::~Measurements() {
  delete pob_spi;
}
