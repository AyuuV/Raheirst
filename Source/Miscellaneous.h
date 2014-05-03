#ifndef __ISDEFINITION_MISCELLANEOUS_HEADER
#define __ISDEFINITION_MISCELLANEOUS_HEADER 1

#include <stdint.h>

#include <time.h>

typedef char __ISType_MemoryUnit;

typedef intmax_t __ISType_Number;
typedef uintmax_t __ISType_Value;

typedef uintmax_t __ISType_Time;

struct __ISStructure_MemoryBuffer {
	__ISType_MemoryUnit* Data;
	__ISType_Value Length;
};

__ISType_Time
__ISFunction_RetrieveProcessorTime(
	const __ISType_Time __localParameter_Resolution,
	const __ISType_Time __localParameter_Offset);

__ISType_Time
__ISFunction_RetrieveWallTime(
	const __ISType_Time __localParameter_Offset);

#endif
