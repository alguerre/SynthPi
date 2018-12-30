#include <gtest/gtest.h>
#include <iostream>
#include "../src/waveform_generator.h"
#include "../src/types.h"
#include "../src/constants.h"
#include "../src/audio_driver.h"


struct AudioDriverTest : testing::Test {
  AudioDriver *ob_audiodriver = NULL;
  WaveformGenerator *ob_waveform = NULL;
  Meas_t st_simple_sine = SimpleSineMeasurements();
  int si_configuration = -1;
  const float f_freq = 440.0;
  float *pf_waveform;

  AudioDriverTest() {
    this->ob_waveform = new WaveformGenerator;
    this->ob_audiodriver = new AudioDriver;
    ob_waveform->SetConfiguration(this->st_simple_sine);
    this->si_configuration = ob_audiodriver->ConfigureAlsa();
  }

  Meas_t SimpleSineMeasurements() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max;
    st_meas.pe_oscillator[0] = OSC_SINE;
    st_meas.pe_oscillator[1] = OSC_NONE;
    st_meas.psi_octave[0] = 1;
    st_meas.psi_octave[1] = 1;
    st_meas.si_lfo = 0;
    st_meas.si_attack_time = 0;
    st_meas.si_decay_time = 0;
    st_meas.si_sustain_level = 0;
    st_meas.si_release_time = 0;
    return st_meas;
  }

  int Play() {
    int si_frames = 0;

    ob_waveform->CreateOscillators(f_freq);
    pf_waveform = ob_waveform->CreateWaveform();
    si_frames = ob_audiodriver->PlaySound(pf_waveform);

    return si_frames;
  }

  ~AudioDriverTest() {
    delete ob_audiodriver;
    delete ob_waveform;
  }

};


TEST_F(AudioDriverTest, Configuration) {
  EXPECT_EQ(this->si_configuration, 0);
}


TEST_F(AudioDriverTest, PlayPeriod) {
  int si_frames = Play();
  EXPECT_EQ(si_frames, SND_PCM_PERIOD_SIZE);
}


TEST_F(AudioDriverTest, PlaySound) {
  int si_played = 0;
  int si_cycles_per_sec = SND_PCM_RATE_STD / SND_PCM_PERIOD_SIZE;

  std::cout << "    Playing waveform" << std::endl;
  for (int i = 0; i < si_cycles_per_sec; i++) {
    Play();
  }

  std::cout << "    Have you listened the sound properly? (yes = 1, no = 0)" << std::endl;
  std::cin >> si_played;
  
  EXPECT_EQ(si_played, 1);
}
