#include "stdafx.h"
#include "Driver.h"



KGUARDED_MUTEX KsGuardedMutex;

extern "C" NTSTATUS DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS status = STATUS_SUCCESS;

	KdPrint(("[+] Loading KsEDR\n"));

	// Initialize Device
	UNICODE_STRING DosDevLinkName = RTL_CONSTANT_STRING(KS_DOS_DEV_LINK_NAME);
	UNICODE_STRING NTDeviceName = RTL_CONSTANT_STRING(KS_NT_DEVICE_NAME);

	PDEVICE_OBJECT Device = nullptr;
	IoDeleteSymbolicLink(&DosDevLinkName);

	KeInitializeGuardedMutex(&KsGuardedMutex);

	DeleteExistingDeviceEntry(&NTDeviceName);

	status = IoCreateDevice(
		DriverObject,
		0,
		&NTDeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&Device
	);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("[+] KsEDR: Failed to create IO device: 0x%x\n", status));
		return status;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE]				= KsDeviceCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]				= KsDeviceClose;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP]				= KsDeviceCleanup;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]		= KsDeviceControl;
	
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("[+] KsDriver: Successfully created IO Device\n"));

	status = IoCreateSymbolicLink(&DosDevLinkName, &NTDeviceName);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("[-] Failed to create symbolic link: 0x%x\n", status));

		IoDeleteDevice(DriverObject->DeviceObject);
		return status;
	}
	
	KdPrint(("[+] KsEDR Successfully loaded\n"));
	if (DriverObject->DriverUnload != DriverUnload)
		DbgRaiseAssertionFailure();
	return status;
}

void DriverUnload(
	PDRIVER_OBJECT DriverObject
)
{
	KdPrint(("[+] Unloaded KsEDR\n"));
	//NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING DosDevLinkName = RTL_CONSTANT_STRING(KS_DOS_DEV_LINK_NAME);

	NTSTATUS status = IoDeleteSymbolicLink(&DosDevLinkName);
	if (status != STATUS_INSUFFICIENT_RESOURCES)
	{
		if (!NT_SUCCESS(status))
			DbgRaiseAssertionFailure();
	}
	
	IoDeleteDevice(DriverObject->DeviceObject);

}

extern "C" void DeleteExistingDeviceEntry(PUNICODE_STRING name)
{
	PDEVICE_OBJECT targetDevice = nullptr;
	PFILE_OBJECT fileObject = nullptr;

	KdPrint(("[+] Checking for existing KsEDR Devices...\n"));
	NTSTATUS delStat = IoGetDeviceObjectPointer(
		name,
		FILE_READ_DATA,
		&fileObject,
		&targetDevice
	);

	if (NT_SUCCESS(delStat))
	{
		// just a safe guard...
		if (targetDevice)
		{
			KdPrint(("[+] Found existing KsEDR Device. Deleting...\n"));
			IoDeleteDevice(targetDevice);
		}
	}
	else 
	{
		KdPrint(("[+] No existing KsEDR devices found.\n"));
	}
}



NTSTATUS KsDeviceCreate(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS KsDeviceClose(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS KsDeviceCleanup(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS KsDeviceControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}