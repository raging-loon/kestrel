#ifndef DRIVER_WIN64_DRIVER_H_
#define DRIVER_WIN64_DRIVER_H_

#include <ntddk.h>
#include <wdf.h>

#define KS_DRIVER_NAME			L"KestrelEDR"
#define KS_NT_DEVICE_NAME		L"\\Device\\KestrelEDRDevice"
#define KS_DOS_DEV_LINK_NAME	L"\\DosDevices\\KestrelEDRDevice"

extern "C" DRIVER_INITIALIZE DriverEntry;
extern "C" DRIVER_UNLOAD	 DriverUnload;

extern "C" void DeleteExistingDeviceEntry(PUNICODE_STRING name);

_Dispatch_type_(IRP_MJ_CREATE)			DRIVER_DISPATCH KsDeviceCreate;
_Dispatch_type_(IRP_MJ_CLOSE)			DRIVER_DISPATCH KsDeviceClose;
_Dispatch_type_(IRP_MJ_CLEANUP)			DRIVER_DISPATCH KsDeviceCleanup;
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)	DRIVER_DISPATCH KsDeviceControl;


#endif // DRIVER_WIN64_DRIVER_H_