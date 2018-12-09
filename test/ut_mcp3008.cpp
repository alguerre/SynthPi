#include <gtest/gtest.h>
#include <iostream>
#include "../src/mcp3008.h"
#include "constants_test.h"


TEST(MCP3008Test, ExtremeCases) {
   /* EXTREMECASES checks those unusual cases which are not covered by the
    * standard use of the class. Only public methods are tested. */

  SpiMcp3008 *pob_spi = SpiMcp3008::GetInstance(8);
  ASSERT_EQ(-1, pob_spi->AnalogRead(k_spi_max_channel+1));
  
  delete pob_spi;

}

