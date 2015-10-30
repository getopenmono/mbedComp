//
//  cy_gpio.h
//  tests
//
//  Created by Kristoffer Andersen on 30/10/2015.
//  Copyright © 2015 Monolit ApS. All rights reserved.
//

#ifndef cy_gpio_h
#define cy_gpio_h

#include "pins.h"
#include <stdint.h>

struct cy_pin
{
    uint8_t val;
    uint8_t mode;
    uint8_t bypass;
};

void CyPins_SetPin(int pin);
void CyPins_ClearPin(int pin);
int  CyPins_ReadPin(int pin);

#endif /* cy_gpio_h */
