#include "mcp3008.h"


SpiMcp3008::SpiMcp3008(int si_spi_channel) {
  this->Setup(si_spi_channel);
}


SpiMcp3008::~SpiMcp3008() {
}


SpiMcp3008* SpiMcp3008::pob_spi = NULL;


SpiMcp3008* SpiMcp3008::GetInstance(int si_spi_channel) {
  if (pob_spi == NULL)
    pob_spi = new SpiMcp3008(si_spi_channel);
  else
    std::cout << "Singleton error" << std::endl;
  return pob_spi;
}


bool SpiMcp3008::Setup(int si_spi_channel) {
  /*
  SETUP initialize the SPI channel in RPi for analog reads.
  */
  this->si_spi_channel = si_spi_channel;

  if ((si_spi_channel != 0) && (si_spi_channel != 1))
    return false;

  if (wiringPiSPISetup(si_spi_channel, k_si_spi_speed) < 0)
    return false;

  return true;
}


int SpiMcp3008::AnalogRead(const int si_chip_channel) {
  /*
  ANALOGREAD reads analog values previously transform to digital by
  chip mcp3008. Three values needs to be sent to chip as data input:
  bit start (1 bit), sgl/diff mode (1 bit) and channel (3 bits). Thus, data
  input is formed by three bytes as:
  [0-0-0-0-0-0-0-StartBit]-[s/d-D2-D1-D0-x-x-x-x]-[x-x-x-x-x-x-x-x]

  Ouput is:
  [?-?-?-?-?-?-?-?]-[?-?-?-?-?-0-B9-B8]-[B7-B6-B5-B4-B3-B2-B1-B0]

  where ? is high impedance and x don't care bits.
  */
  unsigned char puc_spi_data[3];

  if (si_chip_channel > k_si_spi_max_channel)
    return -1;

  puc_spi_data[0] = 0x1;
  puc_spi_data[1] = 0x80 | ((unsigned char) (si_chip_channel << 0x4));
  puc_spi_data[2] = 0x0;

  wiringPiSPIDataRW(this->si_spi_channel, puc_spi_data, 3);

  return ((puc_spi_data[1] << 8) | puc_spi_data[2]) & 0x3FF;
}
