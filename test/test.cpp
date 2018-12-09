#include <gtest/gtest.h>
#include <iostream>
#include <wiringPi.h>
#include "../src/constants.h"

void ConfigureWiringPi() {
  /* CONFIGUREWIRINGPI setups and initializes the wiringPi utilities. */
  wiringPiSetup();
  for (int i = 0; i < k_n_keys; i++) {
    pinMode(pk_keys[i], INPUT);
  }
  for (int i = 0; i < k_n_oscillators; i++){
    pinMode(k_gpio_oscillator_m[i], INPUT);
    pinMode(k_gpio_oscillator_l[i], INPUT);
  }
}


int main(int argc, char **argv){ 
  ConfigureWiringPi();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
