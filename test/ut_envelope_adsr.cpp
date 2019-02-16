#include <gtest/gtest.h>
#include <iostream>
#include <cfloat>
#include "../src/envelope_adsr.h"

#define FLOAT_NEAR_THRESHOLD (1e-6)

struct EnvelopeADSRTest : testing::Test{
  
  float f_startamplitude = 1.2;
  float f_attacktime = 0.1;
  float f_decaytime = 0.05;
  float f_sustainlevel = 1.0;
  float f_releasetime = 0.2;
  
  EnvelopeADSR ob_envelope = EnvelopeADSR(f_startamplitude, 
                                          f_attacktime,
                                          f_decaytime,
                                          f_sustainlevel,
                                          f_releasetime);

  EnvelopeADSRTest() {}

  ~EnvelopeADSRTest() {}

};


TEST_F(EnvelopeADSRTest, ConstructorConfigZero) {
  EnvelopeADSR ob_envelope_test;
  EXPECT_FLOAT_EQ(ob_envelope_test.GetStartAmplitude(), 0.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetAttackTime(), 0.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetDecayTime(), 0.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetSustainLevel(), 0.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetReleaseTime(), 0.0);
}


TEST_F(EnvelopeADSRTest, ConstructorConfig) {
  EnvelopeADSR ob_envelope_test = EnvelopeADSR(1.0, 1.0, 1.0, 1.0, 1.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetStartAmplitude(), 1.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetAttackTime(), 1.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetDecayTime(), 1.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetSustainLevel(), 1.0);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetReleaseTime(), 1.0);
}


TEST_F(EnvelopeADSRTest, SetConfig) {
  EnvelopeADSR ob_envelope_test;
  ob_envelope_test.SetConfig(1.1, 2.2, 3.3, 4.4, 5.5);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetStartAmplitude(), 1.1);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetAttackTime(), 2.2);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetDecayTime(), 3.3);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetSustainLevel(), 4.4);
  EXPECT_FLOAT_EQ(ob_envelope_test.GetReleaseTime(), 5.5);
}


TEST_F(EnvelopeADSRTest, NoteOn) {
  bool b_press = false;

  ob_envelope.NoteOn(1.0);
  b_press = ob_envelope.GetNoteOn();

  EXPECT_EQ(true, b_press);
}


TEST_F(EnvelopeADSRTest, NoteOff) {
  bool b_press = false;

  ob_envelope.NoteOn(1.0);
  ob_envelope.NoteOff(1.5);

  b_press = ob_envelope.GetNoteOn();

  EXPECT_EQ(false, b_press);
}


TEST_F(EnvelopeADSRTest, AttackTime) {
  /* ATTACKTIME checks that after attack time the amplitude is equal to start
   * amplitude, since the note is pressed.  */
  float f_amplitude = 0.0;
  ob_envelope.NoteOn(0.0);
  f_amplitude = ob_envelope.GetAmplitude(f_attacktime);
  EXPECT_FLOAT_EQ(f_amplitude, f_startamplitude);
}


TEST_F(EnvelopeADSRTest, AttackTimeHalf) {
  /* ATTACKTIMEHALF checks that after half of attack time the amplitude is 
   * one half of start amplitude, since the note is pressed.  */
  float f_amplitude = 0.0;
  ob_envelope.NoteOn(0.0);
  f_amplitude = ob_envelope.GetAmplitude(f_attacktime/2.0);
  
  EXPECT_NEAR(f_amplitude, f_startamplitude / 2.0, FLOAT_NEAR_THRESHOLD);
}


TEST_F(EnvelopeADSRTest, DecayTime) {
  /* DECAYTIME checks that after attack time plus decay time the amplitude is 
   * the sustain level, since the note is pressed.  */
  float f_amplitude = 0.0;
  ob_envelope.NoteOn(0.0);
  f_amplitude = ob_envelope.GetAmplitude(f_attacktime + f_decaytime);
  EXPECT_FLOAT_EQ(f_amplitude, f_sustainlevel);
}


TEST_F(EnvelopeADSRTest, SustainLevel) {
  /* SUSTAINLEVEL checks that after attack time plus decay time plus an offset
   * the amplitude is the sustain level, since the note is pressed. */
  float f_amplitude = 0.0;
  ob_envelope.NoteOn(0.0);
  f_amplitude = ob_envelope.GetAmplitude(f_attacktime + f_decaytime + 3.0);
  EXPECT_FLOAT_EQ(f_amplitude, f_sustainlevel);
}


TEST_F(EnvelopeADSRTest, ReleaseTime) {
  /* RELEASETIME checks that after release of note the amplitude goes to 0 
   * in release time. */
  float f_amplitude = 0.0;
  float f_offset = 5.0;
  ob_envelope.NoteOn(0.0);
  ob_envelope.NoteOff(f_offset);
  f_amplitude = ob_envelope.GetAmplitude(f_offset + f_releasetime);
  EXPECT_FLOAT_EQ(f_amplitude, 0.0);
}


TEST_F(EnvelopeADSRTest, ReleaseTimeHalf) {
  /* RELEASETIMEHALF checks that after release of note the amplitude goes to
   * half of sustain level in half of release time. */   

  float f_amplitude = 0.0;
  float f_offset = 5.0;

  ob_envelope.NoteOn(0.0);
  ob_envelope.NoteOff(f_offset);
  f_amplitude = ob_envelope.GetAmplitude(f_offset + f_releasetime/2.0);

  EXPECT_NEAR(f_amplitude, f_sustainlevel/2.0, FLOAT_NEAR_THRESHOLD);
}
