#ifndef __ISDEFINITION_SUPPORT_HEADER
#define __ISDEFINITION_SUPPORT_HEADER 2

#include <stdbool.h>
#include <stdlib.h>

char* __ISSupport_RetrieveParameter(
	const int __localParameter_Limit,
	const char** __localParameter_Array,
	const char* __localParameter_Name,
	char** __externalVariable_Value);

size_t __ISSupport_RetrievePositionInCharArray(
	const char* __localParameter_CharArray,
	const char* __localParameter_TargetCharArray,
	const size_t __localParameter_TargetArraySize,
	const size_t __localParameter_MaxPosition);

bool __ISSupport_SplitTerminatedCharArray(
	const char* __localParameter_Source,
	char** __externalVariable_Start,
	char** __externalVariable_End,
	const char __localParameter_Delimiter,
	const char __localParameter_Terminator);

#endif
