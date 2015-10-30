//
//  cy_spi_test.cpp
//  tests
//
//  Created by Kristoffer Andersen on 30/10/2015.
//  Copyright © 2015 Monolit ApS. All rights reserved.
//

#include "catch.hpp"

extern "C" {
#include <cy_spi.h>
}

SCENARIO("cy software platform spi uses FIFO correctly")
{
    GIVEN("the spi is started")
    {
        uint8_t sendData[4] = {0x13, 0x22, 0x40, 0x8A};
        
        
        SPI0_Start();
        
        WHEN("1 byte is added")
        {
            SPI0_WriteTxData(0x13);
            
            THEN("the SPI byte complete flag must be set")
            {
                uint8_t mask = SPI0_ReadTxStatus() & SPI0_STS_BYTE_COMPLETE;
                REQUIRE(mask == SPI0_STS_BYTE_COMPLETE);
            }
            
            THEN("the read buffer size should be 1")
            {
                REQUIRE(SPI0_GetRxBufferSize() == 1);
            }
            
            THEN("the same byte should be read from the input")
            {
                uint8_t s = SPI0_ReadRxData();
                REQUIRE(s == 0x13);
            }
            
            THEN("after read the empty flag must be set")
            {
                uint8_t mask = SPI0_ReadTxStatus() & SPI0_STS_TX_FIFO_EMPTY;
                REQUIRE(mask == SPI0_STS_TX_FIFO_EMPTY);
            }
        }
        
        WHEN("4 bytes is added")
        {
            for(int i=0;i<4;i++)
                SPI0_WriteTxData(sendData[i]);
            
            THEN("the FIFO should be full")
            {
                uint8_t mask = SPI0_ReadTxStatus() | ~SPI0_STS_TX_FIFO_NOT_FULL;
                REQUIRE(~mask == SPI0_STS_TX_FIFO_NOT_FULL);
            }
            
            THEN("the read fifo should be 4")
            {
                REQUIRE(SPI0_GetRxBufferSize() == 4);
            }
            
            THEN("the input should match the send data")
            {
                for (int i=0; i<4; i++) {
                    REQUIRE(SPI0_ReadRxData() == sendData[i]);
                }
            }
        }
        
        WHEN("the FIFO buffer must loop, (2 + 2 + 2 bytes added and read)")
        {
            SPI0_WriteTxData(sendData[0]);
            SPI0_WriteTxData(sendData[1]);
        }
    }
}