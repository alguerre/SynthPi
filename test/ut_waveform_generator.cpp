#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "../src/waveform_generator.h"
#include "../src/types.h"
#include "../src/constants.h"
#include "../src/audio_driver.h"


bool CheckMeasurements(Meas_t st_measurements, Meas_t st_reference) {
  EXPECT_EQ(st_measurements.si_volume,        st_reference.si_volume);
  for (int i = 0; i < k_n_oscillators; i++) {
    EXPECT_EQ(st_measurements.pe_oscillator[i], st_reference.pe_oscillator[i]);
    EXPECT_EQ(st_measurements.psi_octave[i], st_reference.psi_octave[i]);
  }
  EXPECT_EQ(st_measurements.si_lfo,           st_reference.si_lfo);
  EXPECT_EQ(st_measurements.si_attack_time,   st_reference.si_attack_time);
  EXPECT_EQ(st_measurements.si_decay_time,    st_reference.si_decay_time);
  EXPECT_EQ(st_measurements.si_sustain_level, st_reference.si_sustain_level);
  EXPECT_EQ(st_measurements.si_release_time,  st_reference.si_release_time);
}


Meas_t ZeroMeasurements() {
  Meas_t st_meas_zero;
  st_meas_zero.si_volume = 0;
  st_meas_zero.pe_oscillator[0] = OSC_SINE;
  st_meas_zero.pe_oscillator[1] = OSC_SINE;
  st_meas_zero.psi_octave[0] = 1;
  st_meas_zero.psi_octave[1] = 1;
  st_meas_zero.si_lfo = 0;
  st_meas_zero.si_attack_time = 0;
  st_meas_zero.si_decay_time = 0;
  st_meas_zero.si_sustain_level = 0;
  st_meas_zero.si_release_time = 0;
  return st_meas_zero;
}


TEST(WaveformGeneratorTest, Constructor) {
  WaveformGenerator *ob_waveform;
  ob_waveform = new WaveformGenerator;
  CheckMeasurements(ob_waveform->GetConfiguration(), ZeroMeasurements());
  delete ob_waveform;
}
