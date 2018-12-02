#include<iostream>
#include "mcp3008.h"

int main(void){
    int siSpiChannel = 0;
    int siChipChannel = 0;

    SpiMcp3008 *spi = SpiMcp3008::get_instance(siSpiChannel);

    std::cout << spi->analog_read(siChipChannel) << std::endl;
    return 0;
}

