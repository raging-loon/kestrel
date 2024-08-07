#ifndef DRIVER_WIN32_DRIVER_H_
#define DRIVER_WIN32_DRIVER_H_
#include <wdm.h>
#include <wdf.h>

EVT_WDF_DRIVER_UNLOAD DriverUnload;
EVT_WDF_DRIVER_DEVICE_ADD DriverAdd;
DRIVER_INITIALIZE DriverEntry;


#endif // DRIVER_WIN32_DRIVER_H_