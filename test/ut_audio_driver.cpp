#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "../src/waveform_generator.h"
#include "../src/types.h"
#include "../src/constants.h"
#include "../src/audio_driver.h"
#include <alsa/asoundlib.h>
#include <math.h>


Meas_t SimpleSineMeasurements() {
  Meas_t st_simple_sine;
  st_simple_sine.si_volume = 1;
  st_simple_sine.pe_oscillator[0] = OSC_SINE;
  st_simple_sine.pe_oscillator[1] = OSC_SINE;
  st_simple_sine.psi_octave[0] = 1;
  st_simple_sine.psi_octave[1] = 1;
  st_simple_sine.si_lfo = 0;
  st_simple_sine.si_attack_time = 0;
  st_simple_sine.si_decay_time = 0;
  st_simple_sine.si_sustain_level = 0;
  st_simple_sine.si_release_time = 0;
  return st_simple_sine;
}


/*struct AudioDriverTest : testing::Test {

};*/


TEST(AudioDriverTest, PlaySimpleSine) {
  // Generate waveform
  WaveformGenerator *ob_waveform;
  Meas_t st_sine_config = SimpleSineMeasurements();
  ob_waveform = new WaveformGenerator;
  ob_waveform->SetConfiguration(st_sine_config);
  float *pf_waveform;

  // Play sound
  AudioDriver *ob_audiodriver;
  ob_audiodriver = new AudioDriver;
  ob_audiodriver->ConfigureAlsa();


  std::cout << "    Playing sine wave" << std::endl;

 // for (int i = 0; i < 1000; i++) {
  int si_written_frames = 0;
  float f_time = 0;
  float f_time_elapsed = 1.0 / ((float)SND_PCM_RATE_STD);
  float f_buffer[SND_PCM_PERIOD_SIZE];

  while (1){
    ob_waveform->CreateOscillators(440.0, 0);
    pf_waveform = ob_waveform->CreateWaveform();
    si_written_frames = ob_audiodriver->PlaySound(pf_waveform);
  }

  EXPECT_EQ(si_written_frames, SND_PCM_PERIOD_SIZE);


  // User information
  int si_played = 0;
  std::cout << "    Have you listened the sound properly? (yes = 1, no = 0)" << std::endl;
  std::cin >> si_played;
  EXPECT_EQ(si_played, 1);

  delete ob_waveform;
  delete ob_audiodriver;
}
