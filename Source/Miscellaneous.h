#ifndef __MISCELLANEOUS_HEADER_DEFINITION
#define __MISCELLANEOUS_HEADER_DEFINITION 1

#include <stdint.h>

#include <time.h>

typedef uintmax_t __ISType_Time;

__ISType_Time
__ISFunction_RetrieveProcessorTime(
	const __ISType_Time __localParameter_Resolution,
	const __ISType_Time __localParameter_Offset);

__ISType_Time
__ISFunction_RetrieveWallTime(
	const __ISType_Time __localParameter_Offset);

#endif
