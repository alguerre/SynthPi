#include <iostream>

#include "types.h"
#include "constants.h"

#ifndef _CONFIGURATION_h

#define _CONFIGURATION_h

class Configuration {
/* CONFIGURATION assign a proper equivalence to the measurements integers. */
  friend std::ostream& operator<<(std::ostream&, const Configuration&);

private:
  // Singleton
  //static Configuration* pobConfiguration; // TODO

  // Properties
  Config_t st_configuration;

  // Methods
  void ConfigureOscillators(Meas_t);

  void ConfigureADSR(Meas_t);

  void ConfigureVolume(Meas_t);

public:

  // Constructor
  Configuration();

  // Methods
  Config_t GetConfiguration(Meas_t);
  //static Configuration *get_instance(); // TODO

  // Destructor
  ~Configuration();

};

#endif
