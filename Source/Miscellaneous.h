#ifndef __ISDEFINITION_MISCELLANEOUS_HEADER
#define __ISDEFINITION_MISCELLANEOUS_HEADER 1

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
