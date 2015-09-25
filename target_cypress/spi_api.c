//
//  spi_api.c
//  spiTest
//
//  Created by Kristoffer Andersen on 26/05/15.
//
//

#include "spi_api.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <project.h>
#ifdef __cplusplus
}
#endif

#if DEVICE_SPI1
static const int spi_ports_num = 2;
#else
static const int spi_ports_num = 1;
#endif

struct spi_port_s spi_ports[1+DEVICE_SPI1] =
{
    {
        RP_SPI_HARD_WIRE, NC, 8,0,
        &SPI0_Start, &SPI0_Stop,
        &SPI0_WriteTxData, &SPI0_ReadTxStatus,
        &SPI0_GetRxBufferSize, &SPI0_ReadRxData
    }
#if DEVICE_SPI1
	,{
        TFT_SPI_HARD_WIRE, TFT_SPI_CS, 8, 1,
        &SPI1_Start, &SPI1_Stop,
        &SPI1_WriteTxData, &SPI1_ReadTxStatus,
        &SPI1_GetRxBufferSize, &SPI1_ReadRxData
    }
#endif
};


void spi_init         (spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    for (int i=0; i<spi_ports_num; i++)
    {
        struct spi_port_s *port = &spi_ports[i];
        
        if (port->hardwire == mosi)
        {
            obj->spiPortNum = i;
            obj->port = port;
            if (!port->hardwareCS)
            {
                obj->cs = ssel;
            }
            
            CyGlobalIntEnable;
            port->SPI_Start();
            return;
        }
    }
    
    obj->cs = NC;
    obj->spiPortNum = -1;
    obj->port = NULL;
    
    //CyPins_SetPinDriveMode(ssel, CY_PINS_DM_STRONG);
    //CyPins_SetPin(ssel); // set (active low) CS
}

void spi_free         (spi_t *obj)
{
    if (obj->port == NULL)
        return;
    
    obj->port->SPI_Stop();
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
    if (obj->port != NULL && !obj->port->hardwareCS)
        CyPins_SetPin(obj->cs);
}

int  spi_master_write (spi_t *obj, int value)
{
    //set the CS pin
    //CyPins_ClearPin(obj->cs); // activate chip select
    int timeout = 1000;
    // only 8 bit transfer
    if (obj->port != NULL && obj->port->bitmode == 8)
    {
        obj->port->SPI_WriteTxData(value);
        int to = 0;
        while((obj->port->SPI_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE) == 0 && timeout > to++)
        {
            CyDelayUs(1);
        }
        int retval = 0;
        if (obj->port->SPI_GetRxBufferSize() > 0)
            retval = obj->port->SPI_ReadRxData();
        //CyPins_SetPin(obj->cs);
        if (to < timeout)
            return retval;
        else
            return 0xFF;
    }
    else if (obj->port != NULL && obj->bitmode == 16)
    {
        int retval = 0;
        uint8_t *retarray = (uint8_t*) &retval;
        uint8_t *valarray = (uint8_t*) &value;
        for (int c=0; c<2; c++) {
            int to = 0;
            obj->port->SPI_WriteTxData(valarray[c]);
            
            while ((obj->port->SPI_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE) == 0 && to++ < timeout) {
                CyDelayUs(1);
            }
            
            retarray[c] = obj->port->SPI_ReadRxData();
        }
        
        return retval;
    }
    else if (obj->port != NULL && obj->bitmode == 32)
    {
        int retval = 0;
        uint8_t *retarray = (uint8_t*) &retval;
        uint8_t *valarray = (uint8_t*) &value;
        for (int c=0; c<4; c++) {
            int to = 0;
            obj->port->SPI_WriteTxData(valarray[c]);
            
            while ((obj->port->SPI_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE) == 0 && to++ < timeout) {
                CyDelayUs(1);
            }
            
            retarray[c] = obj->port->SPI_ReadRxData();
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