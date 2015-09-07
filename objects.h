/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

struct spi_s {
    //FT_HANDLE handle;
    PinName clk;
    PinName mosi;
    PinName miso;
    PinName cs;
    char bitmode;
    char lowBytesValue;
    char lowByteDirection;
};
    
struct i2c_s {
    PinName sda;
    PinName sdc;
};

#ifdef __cplusplus
}
#endif

#endif
