//
//  spi.c
//  tests
//
//  Created by Kristoffer Andersen on 30/10/2015.
//  Copyright © 2015 Monolit ApS. All rights reserved.
//

#include "cy_spi.h"
#include <string.h>

uint8_t SPI0_started = 0;
uint8_t SPI0_bufPointer = 0;
uint8_t SPI0_bufPointerRd = 0;
uint8_t SPI0_statusReg = 0x17; //done, idle, empty, not full
uint8_t SPI0_asyncDelay = 0; // no delay
uint8_t SPI0_asyncDelayPtr = 0;
uint8_t SPI0_buffer[4] = {0,0,0,0};

void SPI0_Start()
{
    memset(SPI0_buffer,0,4);
    SPI0_bufPointer = 0;
    SPI0_started = 1;
}

void SPI0_Stop()
{
    SPI0_started = 0;
}

void SPI0_WriteTxData(uint8_t data)
{
    if (!SPI0_started)
        return;
    
    SPI0_buffer[SPI0_bufPointer++] = data;
    
    SPI0_statusReg &= ~(SPI0_STS_TX_FIFO_EMPTY | SPI0_STS_SPI_IDLE); // set not empty AND not idle
    
    if (SPI0_bufPointer % 4 == 0)
    {
        SPI0_statusReg &= ~SPI0_STS_TX_FIFO_NOT_FULL; // set full
        SPI0_bufPointer = 0;
    }
    
    SPI0_statusReg |= SPI0_STS_BYTE_COMPLETE;
}

uint8_t SPI0_ReadTxStatus()
{
    return SPI0_statusReg;
}

uint8_t SPI0_GetRxBufferSize()
{
    return 4;
}

uint8_t SPI0_ReadRxData()
{
    //if ()
    return 0;
}


void SPI1_Start()
{
    
}

void SPI1_Stop()
{
    
}

void SPI1_WriteTxData(uint8_t data)
{
    
}

uint8_t SPI1_ReadTxStatus()
{
    return 0;
}

uint8_t SPI1_GetRxBufferSize()
{
    return 0;
}

uint8_t SPI1_ReadRxData()
{
    return 0;
}