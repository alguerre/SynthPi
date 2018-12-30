#include "audio_driver.h"

// Constructor
AudioDriver::AudioDriver() {
}

int AudioDriver::ConfigureAlsa() {
  /* CONFIGUREALSA is used to configure the Advance Linux Sound Architecture to
  prepare for sound production. */

  int si_error = 0;

  // Open PCM device for playback
  this->pcm_handle = (snd_pcm_t *)malloc(sizeof(snd_pcm_t*));
  si_error = snd_pcm_open(&(this->pcm_handle), "default", SND_PCM_STREAM_PLAYBACK, 0);

  if (si_error < 0) {
    printf("Playback open error: %s\n", snd_strerror(si_error));
    exit(EXIT_FAILURE);
  }

  // Set new parameters to the driver
  si_error = snd_pcm_set_params(this->pcm_handle,
    SND_PCM_FORMAT_FLOAT,
    SND_PCM_ACCESS_RW_INTERLEAVED,
    SND_PCM_CHANNEL_MONO,
    SND_PCM_RATE_STD,
    SND_PCM_SOFT_RESAMPLE,
    SND_PCM_LATENCY);

  if (si_error < 0) {
    fprintf(stderr, "Unable to set hw parameters: %s\n", snd_strerror(si_error));
    exit(EXIT_FAILURE);
  }

  return si_error;
}


int AudioDriver::PlaySound(float f_buffer[SND_PCM_PERIOD_SIZE]) {
  // Plays the buffer and returns the number of written samples.
  return snd_pcm_writei(this->pcm_handle, f_buffer, SND_PCM_PERIOD_SIZE);
}


// Destructor
AudioDriver::~AudioDriver() {
  snd_pcm_close(pcm_handle);
  free(pcm_handle);
}
