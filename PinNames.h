//
//  PinNames.h
//  spiTest
//
//  Created by Kristoffer Andersen on 26/05/15.
//
//

#ifndef spiTest_PinNames_h
#define spiTest_PinNames_h


#ifdef __cplusplus
extern "C" {
#include <project.h>
}
#endif

typedef enum {
    HARD_WIRED,
    ADBUS0 = 0,
    ADBUS1 = 2,
    ADBUS2 = 4,
    ADBUS3 = 8,
    ADBUS4 = 16,
    ADBUS5 = 32,
    ADBUS6 = 64,
    ADBUS7 = 128,
    
    SW_USER = CYREG_PRT4_PC6,
    
    RP_SPI_CLK = HARD_WIRED,
    RP_SPI_MOSI = HARD_WIRED,
    RP_SPI_MISO = HARD_WIRED,
    RP_SPI_CS = CYREG_PRT2_PC6,
    RP_nRESET = CYREG_PRT5_PC0,
    
    TFT_LED_PWR = CYREG_PRT5_PC5,
    
    USBTX,
    USBRX,
    
    NC = -1
} PinName;

#endif
