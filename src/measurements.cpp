#include "measurements.h"

Measurements::Measurements() {
  // Measurements structure initialization
  this->st_measurements.si_volume = 0;
  for (int i = 0; i < k_si_n_oscillators; i++) {
    this->st_measurements.pe_oscillator[i] = OSC_SINE;
    this->st_measurements.psi_octave[i] = 1;
  }
  this->st_measurements.si_lfo_amp = 0;
  this->st_measurements.si_lfo_freq = 0;
  this->st_measurements.si_attack_time = 0;
  this->st_measurements.si_decay_time = 0;
  this->st_measurements.si_sustain_level = 0;
  this->st_measurements.si_release_time = 0;
}


void Measurements::GetOscillators(void) {


  for (int i = 0; i < k_si_n_oscillators; i++) {
    // Select oscillator
    this->st_measurements.pe_oscillator[i] = static_cast<Osc_t> (
        digitalRead(k_psi_gpio_oscillator_m[i])*2 +
        digitalRead(k_psi_gpio_oscillator_l[i])
        );

    // Select octave
    this->st_measurements.psi_octave[i] = 1 +
        digitalRead(k_psi_gpio_octave_m[i])*2 +
        digitalRead(k_psi_gpio_octave_l[i]);
  }
  
  // Configure LFO
  this->st_measurements.si_lfo_amp =
    this->pob_spi->AnalogRead(k_si_pot_lfo_amp);

  this->st_measurements.si_lfo_freq =
    this->pob_spi->AnalogRead(k_si_pot_lfo_freq);

}


void Measurements::GetADSR(void) {
  this->st_measurements.si_attack_time =
      this->pob_spi->AnalogRead(k_si_pot_attack_time);

  this->st_measurements.si_decay_time =
      this->pob_spi->AnalogRead(k_si_pot_decay_time);

  this->st_measurements.si_sustain_level =
      this->pob_spi->AnalogRead(k_si_pot_sustain_time);

  this->st_measurements.si_release_time =
      this->pob_spi->AnalogRead(k_si_pot_release_time);
}


void Measurements::GetVolume(void) {
  this->st_measurements.si_volume =
      this->pob_spi->AnalogRead(k_si_pot_volume);
}


Meas_t Measurements::GetMeasurements() {
  this->GetOscillators();
  this->GetADSR();
  this->GetVolume();

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
		"\nLFO amplitude:  " << ob_meas.st_measurements.si_lfo_amp <<
    "\nLFO frequency:  " << ob_meas.st_measurements.si_lfo_freq <<
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
