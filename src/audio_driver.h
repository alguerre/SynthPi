#ifndef _AUDIODRIVER_h

#define _AUDIODRIVER_h

#include <alsa/asoundlib.h>
#include "constants.h"


class AudioDriver {

private:
  // Singleton
  //static Measurements* pobMeasurements; // TODO

  // Properties
  snd_pcm_t *pcm_handle = NULL;
  const float fk_time_elapsed = 1.0/((float)SND_PCM_RATE_STD);
  float f_time = 0.0;

  // Methods


public:

  // Constructor
  AudioDriver();

  // Methods
  int ConfigureAlsa(void);
  int PlaySound(float(*pf_generate_sound)(float));
  float GetTime(void);
  
  // Destructor
  ~AudioDriver();

};

#endif
