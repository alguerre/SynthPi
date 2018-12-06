#include<iostream>

#include "wiringPi.h"
#include "measurements.h"

int main(void){
  //int siSpiChannel = 0;
  //int siChipChannel = 0;

  //SpiMcp3008 *spi = SpiMcp3008::get_instance(siSpiChannel);
  Measurements ob_measurements;
  // Measurements *ob_measurements = Measurements::get_instance();
  ob_measurements.GetMeasurements();
  ob_measurements.Print();
  for (;;) {
    //std::cout << spi->analog_read(siChipChannel) << std::endl;
    //delay(500);
  }

  return 0;
}

