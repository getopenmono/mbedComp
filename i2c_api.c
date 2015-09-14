
#include <project.h>

#include "i2c_api.h"


void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
    obj->initied = 0;
    obj->sda = sda;
    obj->sdc = scl;
}

/** Configure the I2C frequency.
 *  @param obj The i2c object
 *  @param hz  Frequency in Hz
 */
void i2c_frequency(i2c_t *obj, int hz)
{
    
}

/** Send START command.
 *  @param obj The i2c object
 */
int  i2c_start(i2c_t *obj)
{
    return 0;
}

/** Send STOP command.
 *  @param obj The i2c object
 */
int  i2c_stop(i2c_t *obj)
{
    return 0;
}

/** Blocking reading data.
 *  @param obj     The i2c object
 *  @param address 7-bit address (last bit is 1)
 *  @param data    The buffer for receiving
 *  @param length  Number of bytes to read
 *  @param stop    Stop to be generated after the transfer is done
 *  @return Number of read bytes
 */
int  i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
    if (!obj->initied)
    {
        CyGlobalIntEnable;
        I2C_Start();
        obj->initied = 1;
    }
    
    int status = I2C_MasterReadBuf(address, (uint8_t*)data, length, stop ? I2C_MODE_COMPLETE_XFER : I2C_MODE_NO_STOP);
    
    if (status != 0)
        return status;
    
    while((I2C_MasterStatus() & I2C_MSTAT_XFER_INP) == 1);
    
    return status;
}

/** Blocking sending data.
 *  @param obj     The i2c object
 *  @param address 7-bit address (last bit is 0)
 *  @param data    The buffer for sending
 *  @param length  Number of bytes to wrte
 *  @param stop    Stop to be generated after the transfer is done
 *  @return Number of written bytes
 */
int  i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
    if (!obj->initied)
    {
        CyGlobalIntEnable;
        I2C_Start();
        obj->initied = 1;
    }
    
    int status = I2C_MasterWriteBuf(address, (uint8_t*)data, length, stop ? I2C_MODE_COMPLETE_XFER : I2C_MODE_NO_STOP);
    
    if (status != 0)
        return status;
    
    while ((I2C_MasterStatus() & I2C_MSTAT_XFER_INP) == 1);
    
    return status;
}

/** Reset I2C peripheral. TODO: The action here. Most of the implementation sends stop().
 *  @param obj The i2c object
 */
void i2c_reset(i2c_t *obj)
{
    
}

/** Read one byte.
 *  @param obj The i2c object
 *  @param last Acknoledge
 *  @return The read byte
 */
int  i2c_byte_read(i2c_t *obj, int last)
{
    return 0;
}

/** Write one byte.
 *  @param obj The i2c object
 *  @param data Byte to be written
 *  @return 1 if NAK was received, 0 if ACK was received, 2 for timeout.
 */
int  i2c_byte_write(i2c_t *obj, int data)
{
    return 0;
}
