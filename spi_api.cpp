//
//  spi_api.c
//  spiTest
//
//  Created by Kristoffer Andersen on 26/05/15.
//
//

#include "spi_api.h"
extern "C" {
#include <SPI0.h>
}


void spi_init         (spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    SPI0_Start();
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
    
}

int  spi_master_write (spi_t *obj, int value)
{
    // only 8 bit transfer
    if (value <= 0xFF)
    {
        SPI0_WriteTxData((uint8_t)value);
        if (SPI0_GetRxBufferSize() > 0)
            return SPI0_ReadRxData();
        else
            return 0;
    }
    else
    {
        SPI0_PutArray((uint8_t*) &value, sizeof(int));
        
        if (SPI0_GetRxBufferSize() == 0)
            return 0;
        
        int returnValue;
        uint8_t *bytePtr = (uint8_t*) &returnValue;
        for (unsigned int i=0; i<sizeof(int); i++)
        {
            *bytePtr = SPI0_ReadRxData();
            bytePtr++;
        }
        return returnValue;
    }
    
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