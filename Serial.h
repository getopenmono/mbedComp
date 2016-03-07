
#ifndef __MBED_SERIAL__
#define __MBED_SERIAL__

#include <stdint.h>
#include <PinNames.h>
#include <stdarg.h>

namespace mbed {
    
    class Serial
    {
    protected:
        char strBuffer[128];
        
        static bool usbSerialInited;
        static bool isEnumerated;
        bool uartStarted;
        
        
        void enumerateIfConfigurationChanged();
        
        bool enumerate();
        
    public:
        
        int timeoutMs;
        
        Serial(PinName tx, PinName rx);
        
        int printf(const char* format, ...);

        int vprintf(const char *format, va_list ap);

        bool DTR();
        
        bool IsReady();
        
        static void wakeUpRoutine();
        
        //int scanf(const char *format, ...);
    };
    
}

#endif