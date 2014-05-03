#include "Support.h"

#include <assert.h>

#include <stdbool.h>
#include <stdlib.h>

char* __ISSupport_RetrieveParameter(
	const int __localParameter_Limit,
	const char** __localParameter_Array,
	const char* __localParameter_Name,
	char** __externalVariable_Value)
{
	assert(__localParameter_Array);
	assert(__localParameter_Limit);
	assert(__localParameter_Name);

	char* __localVariable_Value = NULL;
	int __localVariable_Index = 0;

	if(!__externalVariable_Value) { __externalVariable_Value = &__localVariable_Value; }

	for(__localVariable_Index=0;
		__localVariable_Index<__localParameter_Limit;
		__localVariable_Index++)
	{
		assert(__localParameter_Array[__localVariable_Index]);

		char* __localVariable_ParameterName = NULL;
		char* __localVariable_ParameterValue = NULL;

		if(__ISSupport_SplitTerminatedCharArray(
			__localParameter_Array[__localVariable_Index],
			&__localVariable_ParameterName,
			&__localVariable_ParameterValue,
			'=',
			'\0'))
		{
			// Stuff
		}

		if(__localVariable_ParameterName) { free(__localVariable_ParameterName); }
		if(__localVariable_ParameterValue) { free(__localVariable_ParameterValue); }
	}

	return *__externalVariable_Value;
}

size_t __ISSupport_RetrievePositionInCharArray(
	const char* __localParameter_CharArray,
	const char* __localParameter_TargetCharArray,
	const size_t __localParameter_TargetArraySize,
	const size_t __localParameter_MaxPosition)
{
	assert(__localParameter_CharArray);
	assert(__localParameter_MaxPosition);
	assert(__localParameter_TargetArraySize);
	assert(__localParameter_TargetCharArray);

	size_t __localVariable_Index = 0;

	for(__localVariable_Index=0;
		__localVariable_Index<__localParameter_MaxPosition;
		__localVariable_Index++)
	{
		bool __localVariable_Matches = false;
		size_t __localVariable_TargetIndex = 0;

		for(__localVariable_TargetIndex=0;
			__localVariable_TargetIndex<__localParameter_TargetArraySize;
			__localVariable_TargetIndex++)
		{
			if(__localParameter_CharArray[__localVariable_Index]==__localParameter_TargetCharArray[__localVariable_TargetIndex]) {
				__localVariable_Matches = true;
				break;
			}
		}

		if(__localVariable_Matches) { break; }
	}

	return __localVariable_Index;
}

bool __ISSupport_SplitTerminatedCharArray(
	const char* __localParameter_Source,
	char** __externalVariable_Start,
	char** __externalVariable_End,
	const char __localParameter_Delimiter,
	const char __localParameter_Terminator)
{
	assert(__localParameter_Delimiter);
	assert(__localParameter_Source);
	assert(__localParameter_Terminator);
	assert(__externalVariable_End);
	assert(__externalVariable_Start);

	char* __localVariable_Start = NULL;
	char* __localVariable_End = NULL;

	if(!__externalVariable_End) { __externalVariable_End = &__localVariable_End; }
	if(!__externalVariable_Start) { __externalVariable_Start = &__localVariable_Start; }

	// Stuff
	
	if(*__externalVariable_Start&&*__externalVariable_End) { return true; }
	else { return true; }
}
