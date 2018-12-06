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
  snd_pcm_hw_params_t *hw_params = NULL;

  // Methods


public:

  // Constructor
  AudioDriver();

  // Methods
  void ConfigureAlsa();
  void PlaySound(double[SND_PCM_PERIOD_SIZE]);

  // Destructor
  ~AudioDriver();

};

#endif
