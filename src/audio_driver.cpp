#include "audio_driver.h"

// Constructor
AudioDriver::AudioDriver() {
}

void AudioDriver::ConfigureAlsa() {
  /* CONFIGUREALSA is used to configure the Advance Linux Sound Architecture to
  prepare for sound production. */

  // PCM variables initialization
  int si_error = 0;
  unsigned int ui_rate = SND_PCM_RATE_STD;

  // Open PCM device for playback
  this->pcm_handle = (snd_pcm_t *)malloc(sizeof(snd_pcm_t*));

  si_error = snd_pcm_open(&this->pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

  if (si_error < 0) 
    fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(si_error));

  // Set hardware and software parameters
  snd_pcm_hw_params_malloc(&hw_params);

  si_error = snd_pcm_hw_params_any(
    this->pcm_handle,
    this->hw_params
  );

  if (si_error < 0) {
    fprintf(stderr, "Can not configure this PCM device.\n");
    snd_pcm_close(this->pcm_handle);
    exit(1);
  }

  snd_pcm_hw_params_set_access(
    this->pcm_handle,
    this->hw_params,
    SND_PCM_ACCESS_RW_INTERLEAVED
  );


  snd_pcm_hw_params_set_format(
    this->pcm_handle,
    this->hw_params,
    SND_PCM_FORMAT_FLOAT64_LE

  );

  snd_pcm_hw_params_set_channels(
    this->pcm_handle,
    this->hw_params,
    SND_PCM_CHANNEL_MONO
  );

  snd_pcm_hw_params_set_rate_near(
    this->pcm_handle,
    this->hw_params,
    &ui_rate,
    NULL
  );

  // Write new parameters to the driver
  si_error = snd_pcm_hw_params(this->pcm_handle, this->hw_params);

  if (si_error < 0) {
    fprintf(stderr, "Unable to set hw parameters: %s\n", snd_strerror(si_error));
    exit(1);
  }

}


void AudioDriver::PlaySound(double d_buffer[SND_PCM_PERIOD_SIZE]) {
  snd_pcm_writei(this->pcm_handle, d_buffer, SND_PCM_PERIOD_SIZE);
}


// Destructor
AudioDriver::~AudioDriver() {
}
