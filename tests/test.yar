rule GenericPacker : Program
{
meta:
	pool: pe

condition:
	(pe.virtualSize - pe.diskSize) <= 200 
	or
	(size(pe.imports) <= 20 )
	or
	(size(pe.links) <= 2)
}

rule EternalBlueTest : Net
{
meta:
	port: 22 if open

content:
	$c = | 05 00 07 03 (00 * 12) |

condition:
	$c

}

rule CVE_2017_0145_Test : Net
{
meta:
	comment: "stolen from exploit db"
	protocol: SMB

content:
	!ipcrgx = /\\\\<ipregex>\\IPC$\
	$setup = | 23 00 00 00 |
	$trans = "\\PIPE\\\0x00"

condition:
	all 

}


rule GenericKeylogger : Program
{
meta:
	platform: windows
	pool: pe #portable executable

content:
	$s1 = "KeyboardProc"
	$s2 = "SetWindowsHookEx"
	$s3 = "LowLevelKeyBoardHook"
	$s4 = "GetWindowText"
	!s5 = /Reg(.{4,})/

condition:
	3 of ($s* in pe.symbols)
}
