#include "Serial.h"

#include <cstdarg>
#include <cstdio>

extern "C" {
#include <project.h>
}

//extern mono::ui::ConsoleView<176, 190> uiConsole;

using namespace mbed;

bool Serial::usbSerialInited = false;

Serial::Serial(PinName tx, PinName rx)
{
//    uiConsole.WriteLine("Serial contrsuctor, start USB...");
    isEnumerated = false;
    uartStarted = false;
    timeoutMs = 2000;
    
//    uiConsole.WriteLine("USB started");
}

int Serial::printf(const char* format, ...) {
//    uiConsole.WriteLine("usb printf...");
    enumerateIfConfigurationChanged();
    
    std::va_list arg;
	va_start(arg, format);
    vsprintf(strBuffer, format, arg);
    va_end(arg);
    
    if (isEnumerated)
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

void Serial::enumerateIfConfigurationChanged()
{
    if (!uartStarted)
    {
        CyGlobalIntEnable;
        USBUART_Start(0, USBUART_DWR_VDDD_OPERATION);
        uartStarted = true;
    }
    
    
//    uiConsole.WriteLine("enum if config changed...");
    if (isEnumerated)
    {
//        uiConsole.WriteLine("is enum. Is config changed?...");
        if (USBUART_IsConfigurationChanged())
        {
//            uiConsole.WriteLine("config changed! Can get new config?");
            if (0 == USBUART_GetConfiguration())
            {
//                uiConsole.WriteLine("could not get config - no enum!");
                isEnumerated = false;
            }
            else
            {
//                uiConsole.WriteLine("got new config");
                isEnumerated = true;
            }
        }
    }
    else
    {
//        uiConsole.WriteLine("usb not enum, enumerate now...");
        enumerate();
    }
}

bool Serial::enumerate()
{
//    uiConsole.WriteLine("USB enumerate: Get conf...");
    int timeOut = timeoutMs;
    CyGlobalIntEnable;
    while(USBUART_GetConfiguration() == 0 && timeOut > 0)
    {
        CyDelay(1); // wait one MS
        timeOut--;
    }
    
//    if (0 != USBFS_GetConfiguration())
//    {
//        USBUART_IsConfigurationChanged();  /* Clear configuration changes state status */
//        isEnumerated = false;
//        return false;
//    }
    
    if (USBUART_GetConfiguration())
    {
//        uiConsole.WriteLine("Got config!");
        isEnumerated = true;
        USBUART_CDC_Init();
        return true;
    }
    else
    {
//        uiConsole.WriteLine("timeout!");
        isEnumerated = false;
        return false;
    }
}