#include "envelope_adsr.h"
#include "constants.h"


EnvelopeADSR::EnvelopeADSR() {

  // Constructor, properties initialization
  this->SetConfig(0.0, 0.0, 0.0, 0.0, 0.0);

  this->f_trigger_off_time = 0.0;
  this->f_trigger_on_time = 0.0;
  this->b_note_on = false;
}


EnvelopeADSR::EnvelopeADSR(float f_sa,
  float f_at,
  float f_dt,
  float f_sl,
  float f_rt) {

    // Constructor, properties initialization
  this->SetConfig(f_sa, f_at, f_dt, f_sl, f_rt);

  this->f_trigger_off_time = 0.0;
  this->f_trigger_on_time = 0.0;
  this->b_note_on = false;
}


EnvelopeADSR::~EnvelopeADSR() {
    // Destructor
}


void EnvelopeADSR::SetConfig(float f_sa,
  float f_at,
  float f_dt,
  float f_sl,
  float f_rt) {

  // ADSR model
  this->f_start_amplitude = f_sa;
  this->f_attack_time = f_at;
  this->f_decay_time = f_dt;
  this->f_sustain_level = f_sl;
  this->f_release_time = f_rt;
}


float EnvelopeADSR::GetStartAmplitude() {
  return this->f_start_amplitude;
}


float EnvelopeADSR::GetAttackTime() {
  return this->f_attack_time;
}


float EnvelopeADSR::GetDecayTime() {
  return this->f_decay_time;
}


float EnvelopeADSR::GetSustainLevel() {
  return this->f_sustain_level;
}


float EnvelopeADSR::GetReleaseTime() {
  return this->f_release_time;
}


bool EnvelopeADSR::GetNoteOn() {
  return this->b_note_on;
}


void EnvelopeADSR::NoteOn(float f_time_on) {
  /* NOTEOFF store the time in which a note is pressed.*/
  this->f_trigger_on_time = f_time_on;
  this->b_note_on = true;
}


void EnvelopeADSR::NoteOff(float f_time_off) {
  /* NOTEOFF store the time in which a note is released.*/
  this->f_trigger_off_time = f_time_off;
  this->b_note_on = false;
}


float EnvelopeADSR::GetAmplitude(float dTime) {
  /* GETAMPLITUDE returns the amplitude of the wave in a certain time. It is
  obtained according to ADSR model. It is checked whether the note is pressed
  or released to proceed accordingly.*/

  float f_amplitude = 0.0;
  float f_life_time = dTime - this->f_trigger_on_time;

  if (this->b_note_on) {

    if (f_life_time <= this->f_attack_time) {
      // In attack Phase - approach max amplitude
      f_amplitude = (f_life_time / this->f_attack_time) *
        this->f_start_amplitude;
    }

    if ((f_life_time > this->f_attack_time) &&
      (f_life_time <= (this->f_attack_time + this->f_decay_time))) {
      // In decay phase - reduce to sustained amplitude
      f_amplitude = ((f_life_time - this->f_attack_time) / this->f_decay_time) *
        (this->f_sustain_level - this->f_start_amplitude) +
        this->f_start_amplitude;
    }

    if (f_life_time > (this->f_attack_time + this->f_decay_time)) {
      // In sustain phase - dont change until note released
      f_amplitude = this->f_sustain_level;
    }
  }

  else {
    // Note has been released, so in release phase
    f_amplitude = ((dTime - this->f_trigger_off_time) / this->f_release_time) *
      (0.0 - this->f_sustain_level) +
      this->f_sustain_level;
  }

  // Amplitude should not be negative
  if (f_amplitude <= k_f_minimum_amplitude_adsr)
    f_amplitude = 0.0;

  return f_amplitude;
}


std::ostream& operator << (std::ostream &cout, const EnvelopeADSR &ob_envelope)
{
  return std::cout <<
    "Start amplitude:   " << ob_envelope.f_start_amplitude <<
    "\nAttack time:       " << ob_envelope.f_attack_time <<
    "\nDecay time:        " << ob_envelope.f_decay_time <<
    "\nSustain level:     " << ob_envelope.f_sustain_level <<
    "\nRelease time:      " << ob_envelope.f_release_time;   
}
