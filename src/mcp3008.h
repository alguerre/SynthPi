#include<iostream>
#include<wiringPiSPI.h>

class SpiMcp3008 {
private:
    static SpiMcp3008* pobSpi;
    const int csiSpiSpeed = 1000000;
    int siSpiChannel = -1;
    bool setup(int);
public:
    SpiMcp3008(int);
    int analog_read(const int);
    static SpiMcp3008 *get_instance(int);
    ~SpiMcp3008();
};

