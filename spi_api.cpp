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
    int timeout = 500;
    // only 8 bit transfer
    if (value <= 0xFF)
    {
        SPI0_WriteTxData(value);
        int to = 0;
        while((SPI0_ReadTxStatus() & SPI0_STS_SPI_DONE) == 0 && timeout > to++)
        {
            CyDelay(1);
        }
        int retval = 0;
        retval = SPI0_ReadRxData();
        //CyPins_SetPin(obj->cs);
        return retval;
    }
    else
    {
        
        SPI0_PutArray((uint8_t*) &value, sizeof(int));
        int to = 0;
        while((SPI0_ReadTxStatus() & SPI0_STS_SPI_DONE) == 0 && timeout > to++)
        {
            CyDelay(1);
        }
        
        if (SPI0_GetRxBufferSize() == 0)
        {
            //CyPins_SetPin(obj->cs);
            return 0;
        }
        
        
        int returnValue;
        uint8_t *bytePtr = (uint8_t*) &returnValue;
        for (unsigned int i=0; i<sizeof(int); i++)
        {
            *bytePtr = SPI0_ReadRxData();
            bytePtr++;
        }
        
        //CyPins_SetPin(obj->cs);
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