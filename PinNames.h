//
//  PinNames.h
//  spiTest
//
//  Created by Kristoffer Andersen on 26/05/15.
//
//

#ifndef spiTest_PinNames_h
#define spiTest_PinNames_h

typedef enum {
    ADBUS0 = 0,
    ADBUS1 = 2,
    ADBUS2 = 4,
    ADBUS3 = 8,
    ADBUS4 = 16,
    ADBUS5 = 32,
    ADBUS6 = 64,
    ADBUS7 = 128,
    
    SPI_CLK = ADBUS0,
    SPI_MOSI = ADBUS1,
    SPI_MISO = ADBUS2,
    SPI_CS = ADBUS3,
    
    USBTX,
    USBRX,
    
    NC = -1
} PinName;

#endif
