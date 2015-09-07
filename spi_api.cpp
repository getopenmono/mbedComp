//
//  spi_api.c
//  spiTest
//
//  Created by Kristoffer Andersen on 26/05/15.
//
//

#include "spi_api.h"
extern "C" {
#include <project.h>
}


void spi_init         (spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    obj->cs = ssel;
    
    CyGlobalIntEnable;
    SPI0_Start();
    //CyPins_SetPinDriveMode(ssel, CY_PINS_DM_STRONG);
    //CyPins_SetPin(ssel); // set (active low) CS
}

void spi_free         (spi_t *obj)
{
    SPI0_Stop();
}

void spi_format       (spi_t *obj, int bits, int mode, int slave)
{
    obj->bitmode = bits;
}

void spi_frequency    (spi_t *obj, int hz)
{
    
}

void spi_setHighCS(spi_t *obj)
{
    CyPins_SetPin(obj->cs);
}

int  spi_master_write (spi_t *obj, int value)
{
    //set the CS pin
    //CyPins_ClearPin(obj->cs); // activate chip select
    int timeout = 1000;
    // only 8 bit transfer
    if (obj->bitmode == 8)
    {
        SPI0_WriteTxData(value);
        int to = 0;
        while((SPI0_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE) == 0 && timeout > to++)
        {
            CyDelayUs(1);
        }
        int retval = 0;
        if (SPI0_GetRxBufferSize() > 0)
            retval = SPI0_ReadRxData();
        //CyPins_SetPin(obj->cs);
        if (to < timeout)
            return retval;
        else
            return 0xFF;
    }
    else if (obj->bitmode == 32)
    {
        int retval = 0;
        uint8_t *retarray = (uint8_t*) &retval;
        uint8_t *valarray = (uint8_t*) &value;
        for (int c=0; c<4; c++) {
            int to = 0;
            SPI0_WriteTxData(valarray[c]);
            
            while ((SPI0_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE) == 0 && to++ < timeout) {
                CyDelayUs(1);
            }
            
            retarray[c] = SPI0_ReadRxData();
        }
        
        return retval;
    }
    
    return 0xFF;
}


int  spi_slave_receive(spi_t *obj)
{
    return 0;
}

int  spi_slave_read   (spi_t *obj)
{
    return 0;
}

void spi_slave_write  (spi_t *obj, int value)
{
    
}

int  spi_busy         (spi_t *obj)
{
    return 0;
}