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

  // Methods


public:

  // Constructor
  AudioDriver();

  // Methods
  int ConfigureAlsa();
  int PlaySound(float[SND_PCM_PERIOD_SIZE]);
  
  // Destructor
  ~AudioDriver();

};

#endif
