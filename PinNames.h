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
#endif
    
#include <project.h>
    
#ifdef __cplusplus
}
#endif


typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

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
    
    // Auxillary pins
    SW_USER = CYREG_PRT4_PC6,
    BUZZER = CYREG_PRT5_PC3,
    
    //Redpine wireless pins
    RP_SPI_CLK = HARD_WIRED,
    RP_SPI_MOSI = HARD_WIRED,
    RP_SPI_MISO = HARD_WIRED,
    RP_SPI_CS = CYREG_PRT2_PC6,
    RP_nRESET = CYREG_PRT5_PC0,
    
    //SD Card SPI pins
    SD_SPI_CLK = HARD_WIRED,
    SD_SPI_MOSI = HARD_WIRED,
    SD_SPI_MISO = HARD_WIRED,
    SD_SPI_CS = CYREG_PRT2_PC3,
    SD_INSERT_SW = CYREG_PRT5_PC1,
    
    //Display pins
    TFT_LED_PWR = CYREG_PRT5_PC5,
    
    USBTX,
    USBRX,
    
    NC = -1
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    Repeater = 1,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#endif
