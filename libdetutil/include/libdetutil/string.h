#ifndef LIBDETUTIL_STRING_H
#define LIBDETUTIL_STRING_H

#include "libdetutil.h"

LDU_START

/// 
/// PURPOSE
///		Find "srchstr" in "buf"
/// 
LDU_API bool ldu_strsrch(const char* srchstr, const char* buf, int n1len);

LDU_API bool ldu_bytesrch(const unsigned char* srch, const unsigned char* buf, int srchlen, int buflen);

LDU_END

#endif // LIBDETUTIL_STRING_H