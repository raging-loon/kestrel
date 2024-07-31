#include "libdetutil/string.h"
#include "libdetutil/libdetutil.h"

#include <stdint.h>

bool ldu_strsrch(const char* srchstr, const char* buf, int len)
{
	if (!srchstr || !buf) return false;
	
	uint8_t cpos = 0;

	while (*buf)
	{
		if (*(srchstr + cpos ) != *buf)
			cpos = 0;
		else
		{
			++cpos;
			if (cpos == len)
				return true;

		}
		*buf++;
	}
	
	return false;

}

bool ldu_bytesrch(const unsigned char* srch, const unsigned char* buf, int srchlen, int buflen)
{
	if (!srch || !buf) return false;

	uint8_t cpos = 0;

	const unsigned char* bufend = buf + buflen;
	
	while (buf <= bufend)
	{
		if (*(srch + cpos) != *buf)
			cpos = 0;
		else
		{
			if (++cpos == srchlen)
				return true;
		}

		*buf++;
	}


	return false;
}
	