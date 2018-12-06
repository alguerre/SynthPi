#include <iostream>

#include "types.h"
#include "constants.h"
#include "mcp3008.h"

#ifndef _MEASUREMENTS_h

#define _MEASUREMENTS_h

class Measurements {

private:
  // Singleton
  //static Measurements* pobMeasurements; // TODO
    
  // Properties
  Meas_t st_measurements;
  SpiMcp3008 *pob_spi = SpiMcp3008::GetInstance(k_spi_channel);

  // Methods
  void ConfigureOscillators();

  void ConfigureADSR();

  void ChangeVolume();

public:

  // Constructor
  Measurements();

  // Methods
  Meas_t GetMeasurements();
  //static Measurements *get_instance(); // TODO
  void Print();

  // Destructor
  ~Measurements();

};

#endif
