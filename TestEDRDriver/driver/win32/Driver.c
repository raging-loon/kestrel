#include "ProcessHook.h"
#include "Driver.h"
#include <wdm.h>

BOOLEAN processHookWasSet = FALSE;
WDFDEVICE Device;
NTSTATUS DriverEntry(
	PDRIVER_OBJECT driverObject,
	PUNICODE_STRING registryPath
)
{
	DbgPrint("[+] Driver loading...\n");
	
	WDF_DRIVER_CONFIG conf;
	WDF_DRIVER_CONFIG_INIT(&conf, NULL);
	conf.EvtDriverUnload = DriverUnload;
	conf.EvtDriverDeviceAdd = DriverAdd;
	NTSTATUS status = WdfDriverCreate(driverObject, registryPath, WDF_NO_OBJECT_ATTRIBUTES, &conf, WDF_NO_HANDLE);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("Failed to create WDF Driver\n");
		return status;
	}

	status = PsSetCreateProcessNotifyRoutineEx(KsProcessHook, FALSE);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Failed to set process hook\n");
		return status;
	}

	processHookWasSet = TRUE;

	DbgPrint("[+] Driver Loaded successfully\n");
	return STATUS_SUCCESS;

}


VOID DriverUnload(WDFDRIVER driver)
{
	UNREFERENCED_PARAMETER(driver);

	if(processHookWasSet)
		PsSetCreateProcessNotifyRoutineEx(KsProcessHook, TRUE);
	DbgPrint("[+] Driver unloaded\n");
}

NTSTATUS DriverAdd(
	WDFDRIVER Driver,
	PWDFDEVICE_INIT DeviceInit
)
{
	UNREFERENCED_PARAMETER(Driver);
	return WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &Device);
}