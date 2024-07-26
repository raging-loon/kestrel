#include <stdio.h>
#include <stdbool.h>

bool strsrch(const char* src, const char* target, int len);

int main(int argc, char** argv)
{
    const char * target = "test";

    const char* test_data =
    "";


    strsrch(test_data, target, 4);


}

bool strsrch(const char* src, const char* target, int len)
{
    if(!*target) return false;

    int spos = 0;


    while(*src)
    {

        if(*src != *(target + spos))
        {
            spos = 0;
        }
        else
        {
            spos++;
            if(spos == len)
                break;
        }
        *src++;
    }
    return true;
}

struct IPHeader
{
    int y;
} typedef IPHeader;
struct TCPHeader
{
     int x;
} typedef TCPHeader;

bool bytesearch(const unsigned char* source, const unsigned char* target, int len );


bool rule_callback_eternal_blue_test(
    const unsigned char * data,
    IPHeader* iph,
    TCPHeader* tcph,
    unsigned int totalLength
)
{
    return bytesearch(
        data, 
        "\x95\x00\x07\x03\x00\x00\x00\x00"\
        "\x00\x00\x00\x00\x00\x00\x00\x00", 
        16    
    );
}

bool regex_search(void*, void*);

bool rule_callback_cve_2017_0145_test(
    const unsigned char *data,
    IPHeader * iph,
    TCPHeader* tcph
)
{
	return regex_search(data, "/\\\\<ipregex>\\IPC$\\") &&
		   byte_search(data, "\x23\x00\x00\x00") &&
		   byte_search(data, "\\PIPE\\\0x00");

}

typedef const char* string;

struct _ProgramData
{
    int symbols;
} typedef ProgramData;

bool rule_callback_generic_keylogger(ProgramData * pd)
{
	string targets[] = {
		"KeyBoardProc", ...
	};

	int detected = 0;
	for(int i = 0; i < 4; i++)
	{
		if(function_search(pd.symbols, targets[i]))
			detected++;
	}

	if(regex_search(pd.symbols, targets[4]))
		detected++;

	return detected >= 3;
}