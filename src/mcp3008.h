#include<iostream>
#include<wiringPiSPI.h>
#include "constants.h"
#ifndef _MCP3008_h

#define _MCP3008_h

class SpiMcp3008 {
private:
    static SpiMcp3008* pob_spi;
    int si_spi_channel = -1;
    bool Setup(int);
public:
    SpiMcp3008(int);
    int AnalogRead(const int);
    static SpiMcp3008 *GetInstance(int);
    ~SpiMcp3008();
};

#endif