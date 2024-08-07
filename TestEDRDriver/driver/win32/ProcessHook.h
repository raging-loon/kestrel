#ifndef DRIVER_WIN32_PROCESS_HOOK_H_
#define DRIVER_WIN32_PROCESS_HOOK_H_

#include <ntddk.h>

VOID KsProcessHook(
	PEPROCESS Process,
	HANDLE ProcessID,
	PPS_CREATE_NOTIFY_INFO CreateInfo
);


#endif // DRIVER_WIN32_PROCESS_HOOK_H_