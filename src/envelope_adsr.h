#ifndef _ENVELOPEADSR_h
#define _ENVELOPEADSR_h

#include <string>
#include <iostream>

class EnvelopeADSR {

  friend std::ostream &operator<<(std::ostream &, const EnvelopeADSR &);

private:
  // Properties
  float f_attack_time;
  float f_decay_time;
  float f_sustain_level;
  float f_release_time;
  float f_start_amplitude;
  float f_trigger_off_time;
  float f_trigger_on_time;
  bool  b_note_on;  

public:
  // Constructor
  EnvelopeADSR();
  EnvelopeADSR(float, float, float, float, float);

  // Methods   
  void SetConfig(float, float, float, float, float);
  void NoteOn(float);
  void NoteOff(float);
  float GetAmplitude(float);

  float GetStartAmplitude(void);
  float GetAttackTime(void);
  float GetDecayTime(void);
  float GetSustainLevel(void);
  float GetReleaseTime(void);
  bool GetNoteOn(void);

  // Destructor
  ~EnvelopeADSR();

};

#endif
