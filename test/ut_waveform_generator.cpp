#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../src/waveform_generator.h"
#include "../src/types.h"
#include "../src/constants.h"

struct GenerateConfig {
  GenerateConfig() {}
  ~GenerateConfig() {}

  static Meas_t ZeroMeasurements() {
    Meas_t st_meas;
    st_meas.si_volume = 0;
    st_meas.pe_oscillator[0] = OSC_NONE;
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

  static Meas_t SineConfig() {
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

  static Meas_t SquareConfig() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max;
    st_meas.pe_oscillator[0] = OSC_SQUARE;
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

  static Meas_t TriangleConfig() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max;
    st_meas.pe_oscillator[0] = OSC_TRIANGLE;
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

  static Meas_t SawtoohConfig() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max;
    st_meas.pe_oscillator[0] = OSC_SAW;
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

  static Meas_t DoubleConfig() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max;
    st_meas.pe_oscillator[0] = OSC_TRIANGLE;
    st_meas.pe_oscillator[1] = OSC_SQUARE;
    st_meas.psi_octave[0] = 1;
    st_meas.psi_octave[1] = 1;
    st_meas.si_lfo = 0;
    st_meas.si_attack_time = 0;
    st_meas.si_decay_time = 0;
    st_meas.si_sustain_level = 0;
    st_meas.si_release_time = 0;
    return st_meas;
  }

  static Meas_t VolumeZeroConfig() {
    Meas_t st_meas;
    st_meas.si_volume = 0;
    st_meas.pe_oscillator[0] = OSC_SQUARE;
    st_meas.pe_oscillator[1] = OSC_NONE;
    st_meas.psi_octave[0] = 1;
    st_meas.psi_octave[1] = 2;
    st_meas.si_lfo = 0;
    st_meas.si_attack_time = 0;
    st_meas.si_decay_time = 0;
    st_meas.si_sustain_level = 0;
    st_meas.si_release_time = 0;
    return st_meas;
  }

  static Meas_t VolumeHalfConfig() {
    Meas_t st_meas;
    st_meas.si_volume = k_si_adc_max/2;
    st_meas.pe_oscillator[0] = OSC_SQUARE;
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

};


struct GenerateReference {
  GenerateReference() {}
  
  ~GenerateReference() {}
  
  static float ReferenceOscillator(float f_freq, float f_time, Osc_t e_osc) {
    float f_output = 0.0;
    float f_w_t = f_freq * 2.0 * M_PI * f_time;

    switch (e_osc) {
    case OSC_SINE:
      f_output = sin(f_w_t);
      break;

    case OSC_SQUARE:
      f_output = sin(f_w_t) > 0 ? 1.0 : -1.0;
      break;

    case OSC_TRIANGLE:
      f_output = asin(sin(f_w_t)) * M_2_PI;
      break;

    case OSC_SAW:
      f_output = M_2_PI * (f_freq * M_PI * fmod(f_time, 1.0 / f_freq) - M_PI_2);
      break;

    case OSC_NOISE:
      f_output = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
      break;

    default:
      f_output = 0.0;
    }

    return f_output;
  }

  static std::vector<float> GenerateReferenceVector(float f_freq, Osc_t e_osc, int si_size) {
    float f_time = 0.0;
    const float f_time_elapsed = 1.0 / ((float)SND_PCM_RATE_STD);
    std::vector<float> vf_reference;
    float f_sample = 0.0;

    for (int i = 0; i < si_size; i++) {
      f_sample = GenerateReference::ReferenceOscillator(f_freq, f_time, e_osc); 
      vf_reference.push_back(f_sample);
      f_time += f_time_elapsed;
    }

    return vf_reference;
  }

};


struct WaveformGeneratorTest : testing::Test {
  WaveformGenerator *ob_waveform = NULL;
  const float f_freq = 440.0;


  WaveformGeneratorTest() {
    ob_waveform = new WaveformGenerator;
  }


  void CheckMeasurements(Meas_t st_measurements, Meas_t st_reference) {
    EXPECT_EQ(st_measurements.si_volume, st_reference.si_volume);
    for (int i = 0; i < k_n_oscillators; i++) {
      EXPECT_EQ(st_measurements.pe_oscillator[i], st_reference.pe_oscillator[i]);
      EXPECT_EQ(st_measurements.psi_octave[i], st_reference.psi_octave[i]);
    }
    EXPECT_EQ(st_measurements.si_lfo, st_reference.si_lfo);
    EXPECT_EQ(st_measurements.si_attack_time, st_reference.si_attack_time);
    EXPECT_EQ(st_measurements.si_decay_time, st_reference.si_decay_time);
    EXPECT_EQ(st_measurements.si_sustain_level, st_reference.si_sustain_level);
    EXPECT_EQ(st_measurements.si_release_time, st_reference.si_release_time);
  }

  
  std::vector<float> Create100Periods(Meas_t st_config) {
    std::vector<float> vf_waveform;
    float *pf_waveform;

    this->ob_waveform->SetConfiguration(st_config);

    for (int i = 0; i < 100; i++) {
      this->ob_waveform->CreateOscillators(this->f_freq);
      pf_waveform = ob_waveform->CreateWaveform();

      for (int j = 0; j < SND_PCM_PERIOD_SIZE; j++) {
        vf_waveform.push_back(pf_waveform[j]);
      }
    }

    return vf_waveform;
  }


  void Vector2CSV(std::vector<float> vf_waveform, std::string s_filename) {
    std::ofstream csv;
    csv.open(s_filename);

    for (int i = 0; i < vf_waveform.size(); i++) {
      csv << vf_waveform.at(i) << std::endl;
    }

    csv.close();
  }

  
  int CompareVector(std::vector<float> vf_waveform, std::vector<float> vf_reference) {
    int si_equal = 0;

    if (vf_waveform == vf_reference) {
      si_equal = 1;
    }

    return si_equal;
  }


  ~WaveformGeneratorTest() {
    delete this->ob_waveform;
  }

};


TEST_F(WaveformGeneratorTest, NoneOscillator) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::ZeroMeasurements();
  std::string s_filename = "NoneOscillator.csv";
  std::string s_reference = "NoneReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_NONE, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);
}


TEST_F(WaveformGeneratorTest, SineOscillator) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::SineConfig();
  std::string s_filename = "SineOscillator.csv";
  std::string s_reference = "SineReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_SINE, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);

  Vector2CSV(vf_waveform, s_filename);
  Vector2CSV(vf_reference, s_reference);
}


TEST_F(WaveformGeneratorTest, SquareOscillator) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::SquareConfig();
  std::string s_filename = "SquareOscillator.csv";
  std::string s_reference = "SquareReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_SQUARE, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);

  Vector2CSV(vf_waveform, s_filename);
  Vector2CSV(vf_reference, s_reference);
}


TEST_F(WaveformGeneratorTest, TriangleOscillator) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::TriangleConfig();
  std::string s_filename = "TriangleOscillator.csv";
  std::string s_reference = "TriangleReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_TRIANGLE, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);

  Vector2CSV(vf_waveform, s_filename);
  Vector2CSV(vf_reference, s_reference);
}


TEST_F(WaveformGeneratorTest, SawtoothOscillator) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::SawtoohConfig();
  std::string s_filename = "SawtoothOscillator.csv";
  std::string s_reference = "SawtoothReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_SAW, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);

  Vector2CSV(vf_waveform, s_filename);
  Vector2CSV(vf_reference, s_reference);
}


TEST_F(WaveformGeneratorTest, VolumeZero) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::VolumeZeroConfig();
  std::string s_filename = "VolumeZeroOscillator.csv";
  std::string s_reference = "VolumeZeroReference.csv";

  vf_waveform = Create100Periods(st_configuration);
  vf_reference = GenerateReference::GenerateReferenceVector(f_freq, OSC_NONE, vf_waveform.size());

  si_equal = CompareVector(vf_waveform, vf_reference);

  EXPECT_EQ(si_equal, 1);

  Vector2CSV(vf_waveform, s_filename);
  Vector2CSV(vf_reference, s_reference);
}


TEST_F(WaveformGeneratorTest, VolumeHalf) {
  int si_equal = 0;
  std::vector<float> vf_waveform;
  std::vector<float> vf_reference;
  Meas_t st_configuration = GenerateConfig::VolumeHalfConfig();
  std::string s_filename = "VolumeHalfOscillator.csv";

  vf_waveform = Create100Periods(st_configuration);

  double f_max = *max_element(vf_waveform.begin(), vf_waveform.end());
  double f_min = *min_element(vf_waveform.begin(), vf_waveform.end());

  EXPECT_FLOAT_EQ(f_max, 0.5);
  EXPECT_FLOAT_EQ(f_min, -0.5);

  Vector2CSV(vf_waveform, s_filename);
}

TEST_F(WaveformGeneratorTest, DoubleOscillator) {
  // TODO 
}