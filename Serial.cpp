#include "Serial.h"

#include <cstdarg>
#include <cstdio>
extern "C" {
#include <project.h>
}

using namespace mbed;

Serial::Serial(PinName tx, PinName rx)
{
    
    CyGlobalIntEnable;
    USBUART_Start(0, USBUART_3V_OPERATION);
    while(USBUART_GetConfiguration());
    USBUART_CDC_Init();
    
	if (rx != USBRX || tx!= USBTX)
	{
        this->printf("Serial must be constructed using the USBTX and USBRX pins!\n");
	}
}

int Serial::printf(const char* format, ...) {
    std::va_list arg;
	va_start(arg, format);
    vsprintf(strBuffer, format, arg);
    va_end(arg);
    USBUART_PutString(strBuffer);
    
    return 0;
}

// int Serial::scanf(const char* format, ...) {
//     std::va_list arg;
//     va_start(arg, format);
//
//
//     fflush(_file);
//     int r = vfscanf(_file, format, arg);
//     va_end(arg);
//     return r;
// }