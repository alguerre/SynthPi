#include "mcp3008.h"


SpiMcp3008::SpiMcp3008(int siSpiChannel){
    this->setup(siSpiChannel);
}


SpiMcp3008::~SpiMcp3008(){
}


SpiMcp3008* SpiMcp3008::pobSpi = NULL;


SpiMcp3008* SpiMcp3008::get_instance(int siSpiChannel){
    if (pobSpi == NULL)
        pobSpi = new SpiMcp3008(siSpiChannel);
    else
        std::cout << "Singleton error" << std::endl;
    return pobSpi;
}


bool SpiMcp3008::setup(int siSpiChannel){
    /*
    SETUP initialize the SPI channel in RPi for analog reads.
    */
    this->siSpiChannel = siSpiChannel;

    if ((siSpiChannel != 0) && (siSpiChannel != 1))
        return false;

    if (wiringPiSPISetup(siSpiChannel, this->csiSpiSpeed) < 0)
        return false;
    
    return true;
}


int SpiMcp3008::analog_read(const int csiChipChannel){
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
    unsigned char pucSpiData[3];

    pucSpiData[0] = 0x1;
    pucSpiData[1] = 0x80 | (csiChipChannel << 4);
    pucSpiData[2] = 0x0; 
    
    wiringPiSPIDataRW (this->siSpiChannel, pucSpiData, 3) ;

    return ((pucSpiData [1] << 8) | pucSpiData [2]) & 0x3FF ;
}
