#include "ProcessHook.h"

VOID KsProcessHook(
	PEPROCESS Process,
	HANDLE ProcessID,
	PPS_CREATE_NOTIFY_INFO CreateInfo
)
{
	if (CreateInfo && CreateInfo->CommandLine)
	{
		DbgPrint(
			"KSEDR: New Process at %p (id = 0x%p) created. Creator = %Ix:%Ix\n"\
			"		command line: %wZ\n"
			"		filename: %wZ\n",
			Process,
			ProcessID,
			(ULONG_PTR)CreateInfo->CreatingThreadId.UniqueProcess,
			(ULONG_PTR)CreateInfo->CreatingThreadId.UniqueThread,
			CreateInfo->CommandLine,
			CreateInfo->ImageFileName
		);

		UNICODE_STRING string;
		RtlInitUnicodeString(&string, L"\"C:\\Windows\\system32\\notepad.exe\" ");
		if (RtlCompareUnicodeString(CreateInfo->CommandLine,&string, TRUE) == 0)
		{
			DbgPrint("Blocking notepad.exe... :-)\n");
			CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		}

	}
}