#ifndef __ISDEFINITION_SUPPORT_HEADER
#define __ISDEFINITION_SUPPORT_HEADER 2

#include <stdbool.h>
#include <stdlib.h>

char* __ISSupport_CopyCharArray(
	const char* __localParameter_PrimarySource,
	const size_t __localParameter_PrimaryLength,
	const char* __localParameter_SecondarySource,
	const size_t __localParameter_SecondaryLength,
	char** __externalVariable_Target);

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
	const char* __localParameter_Delimiters,
	const char* __localParameter_Terminators,
	const size_t __localParameter_DelimiterLength,
	const size_t __localParameter_TerminatorLength,
	const char* __localParameter_TerminatingSequence,
	const size_t __localParameter_TerminationSequenceLength);

#endif
