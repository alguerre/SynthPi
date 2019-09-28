#include "audio_driver.h"
#include <iostream>
// Constructor
AudioDriver::AudioDriver() {
  this->f_time = 0.0;
}

int AudioDriver::ConfigureAlsa(void) {
  /* CONFIGUREALSA is used to configure the Advance Linux Sound Architecture to
  prepare for sound production. */

  // PCM variables initialization
  int si_error = 0;
  snd_pcm_hw_params_t *hw_params = NULL;
  unsigned int ui_rate = SND_PCM_RATE_STD;

  // Open PCM device for playback
  pcm_handle = (snd_pcm_t *) malloc(sizeof(snd_pcm_t*));
  si_error = snd_pcm_open(&pcm_handle,
                          "default",
                          SND_PCM_STREAM_PLAYBACK,
                          0);
  if (si_error < 0){
      fprintf(stderr,
          "Unable to open pcm device: %s\n",
          snd_strerror(si_error));
  }

  // Set hardware and software parameters
  snd_pcm_hw_params_malloc(&hw_params);

  si_error = snd_pcm_hw_params_any(
      pcm_handle,
      hw_params
  );
  if (si_error < 0){
      fprintf(stderr, "Can not configure this PCM device.\n");
      snd_pcm_close(pcm_handle);
      exit(1);
  }

  snd_pcm_hw_params_set_access(
      pcm_handle,
      hw_params,
      SND_PCM_ACCESS_RW_INTERLEAVED
  );

  snd_pcm_hw_params_set_format(
      pcm_handle,
      hw_params,
      SND_PCM_FORMAT_FLOAT_LE
  );

  snd_pcm_hw_params_set_channels(
      pcm_handle,
      hw_params,
      SND_PCM_CHANNEL_MONO
  );

  snd_pcm_hw_params_set_rate_near(
      pcm_handle,
      hw_params,
      &ui_rate,
      NULL
  );

  // Write new parameters to the driver
  si_error = snd_pcm_hw_params(pcm_handle, hw_params);
  if (si_error < 0){
      fprintf(stderr, "Unable to set hw parameters: %s\n", snd_strerror(si_error));
      exit(1);
  }

  return si_error;
}


int AudioDriver::PlaySound(float(*pf_generate_sound)(float)) {
  // Buffer initialization
  float pf_buffer[SND_PCM_PERIOD_SIZE] = {0};

  // Fill buffer
  for (int i = 0; i < SND_PCM_PERIOD_SIZE; i++){
    pf_buffer[i] = pf_generate_sound(f_time);
    this->f_time += this->fk_time_elapsed;
  }

  // Plays the buffer and returns the number of written samples.
  return snd_pcm_writei(this->pcm_handle, pf_buffer, SND_PCM_PERIOD_SIZE);
}


float AudioDriver::GetTime(void) {
  return this->f_time;
}

// Destructor
AudioDriver::~AudioDriver() {
  snd_pcm_close(pcm_handle);
  free(pcm_handle);
}
