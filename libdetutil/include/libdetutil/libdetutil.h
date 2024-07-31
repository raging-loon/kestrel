#ifndef LIBDETUTIL_LIBDETUTIL_H_
#define LIBDETUTIL_LIBDETUTIL_H_

#ifdef __cplusplus
#define LDU_START extern "C" {
#define LDU_END }

#else

#define LDU_START
#define LDU_END
#endif // __cplusplus


#ifdef _MSC_VER
#define LDU_API __declspec(dllexport)
#else 
# define LDU_API
#endif // MSVC

#define LDU_VERSION_MAJOR 0
#define LDU_VERSION_MINOR 1

#include <stdbool.h>


#endif // LIBDETUTIL_LIBDETUTIL_H_