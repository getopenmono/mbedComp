
#ifndef __MBED_SERIAL__
#define __MBED_SERIAL__

#include <stdint.h>
#include <PinNames.h>

namespace mbed {
    
    class Serial
    {
    protected:
        char strBuffer[256];
    public:
        
        Serial(PinName tx, PinName rx);
        
        int printf(const char* format, ...);
        
        //int scanf(const char *format, ...);
    };
    
}

#endif