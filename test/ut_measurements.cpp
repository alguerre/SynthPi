#include <gtest/gtest.h>
#include <iostream>
#include "../src/measurements.h"
#include "constants_test.h"

// Initialization of common variables
Measurements ob_measurements;
Meas_t st_measurements;
double d_max_pot_value = k_spi_bits * 
  (k_pot_resistor_max)/(k_pot_resistor_max + k_pot_resistor_aux);


void PressEnter(void){
  /* PRESSENTER force the user to press enter to continue. Useful when it is 
   * necessary to manage the physical interface..*/
  std::cout << "    Press enter when ready..." << std::endl;
  std::cin.get();
}


TEST(MeasurementsTest, ConfigureOscillators) {
   /* CONFIGUREOSCILLATORS tests that the specified switches for oscillator 
    * selection have the expected behavior and check the possible output values
    * of the LFO potentiometer, by checking its minimum and maximum value 
    * configurations. Connections and software are tested simultaneously.*/

  std::cout << "ConfigureOscillators" << std::endl;
  std::cout << "  1. Down switches for oscillator selection" << std::endl;
  std::cout << "  2. Turn LFO potentiometer to minimum" << std::endl;
  PressEnter(); 

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(0, st_measurements.pe_oscillator[0]);
  EXPECT_EQ(0, st_measurements.pe_oscillator[1]);
  EXPECT_EQ(0, st_measurements.si_lfo);

  std::cout << "ConfigureOscillators" << std::endl;
  std::cout << "  1. Up switches for oscillator selection" << std::endl;
  std::cout << "  2. Turn LFO potentiometer to maximum" << std::endl;
  PressEnter(); 

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(3, st_measurements.pe_oscillator[0]);
  EXPECT_EQ(3, st_measurements.pe_oscillator[1]);
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_lfo);

  std::cout << "ConfigureOscillators" << std::endl;
  std::cout << "  1. Configuration 0 1 in both oscillators." << std::endl;
  PressEnter();

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(1, st_measurements.pe_oscillator[0]);
  EXPECT_EQ(1, st_measurements.pe_oscillator[1]);

  std::cout << "ConfigureOscillators" << std::endl;
  std::cout << "  1. Configuration 1 0 in both oscillators." << std::endl;
  PressEnter();

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(2, st_measurements.pe_oscillator[0]);
  EXPECT_EQ(2, st_measurements.pe_oscillator[1]);
}


TEST(MeasurementsTest, ConfigureADSR){
  /* CONFIGUREADSR tests that the specified potentiometers for ADSR 
   * configuration are able to reach the minimum value and exceed a maximum 
   * threshold. Connections and software are tested simultaneously.*/

  std::cout << "ConfigureADSR" << std::endl;
  std::cout << "  1. Turn ADSR potentiometers to minimum" << std::endl;
  PressEnter(); 

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(0, st_measurements.si_attack_time);
  EXPECT_EQ(0, st_measurements.si_decay_time);
  EXPECT_EQ(0, st_measurements.si_sustain_level);
  EXPECT_EQ(0, st_measurements.si_release_time);

  std::cout << "ConfigureADSR" << std::endl;
  std::cout << "  1. Turn ADSR potentiometers to maximum" << std::endl;
  PressEnter();

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_attack_time);
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_decay_time);
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_sustain_level);
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_release_time);
}


TEST(MeasurementsTest, ChangeVolume){ 
  /* CHANGEVOLUME tests that the potentiometer is able to reach the minimum
  * value and exceed a maximum threshold. Connections and software are tested 
  * simultaneously.*/

  std::cout << "ChangeVolume" << std::endl;
  std::cout << "  1. Turn Volume potentiometer to minimum" << std::endl;
  PressEnter();

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_EQ(0, st_measurements.si_volume);

  std::cout << "ChangeVolume" << std::endl;
  std::cout << "  1. Turn Volume potentiometer to maximum" << std::endl;
  PressEnter(); 

  st_measurements = ob_measurements.GetMeasurements();
  EXPECT_LT(k_pot_max_threshold * d_max_pot_value, st_measurements.si_volume);
}

