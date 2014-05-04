#include "Support.h"

#include <assert.h>

#include <stdbool.h>
#include <stdlib.h>

#include <strings.h>

char*
__ISSupport_CopyCharArray(
	const char* __localParameter_PrimarySource,
	const size_t __localParameter_PrimaryLength,
	const char* __localParameter_SecondarySource,
	const size_t __localParameter_SecondaryLength,
	char** __externalVariable_Target)
{
	assert(__localParameter_PrimaryLength||__localParameter_SecondaryLength);
	assert(__localParameter_PrimarySource||__localParameter_SecondarySource);

	char* __localVariable_Target = NULL;
	size_t __localVariable_Index = 0;
	size_t __localVariable_PrimarySize = 0;
	size_t __localVariable_SecondarySize = 0;

	if(__localParameter_PrimarySource) { __localVariable_PrimarySize = sizeof(*__localParameter_PrimarySource)*__localParameter_PrimaryLength; }
	if(__localParameter_SecondarySource) { __localVariable_SecondarySize = sizeof(*__localParameter_SecondarySource)*__localParameter_SecondaryLength; }

	if(!(__localVariable_PrimarySize+__localVariable_SecondarySize)) { return NULL; }

	if(!__externalVariable_Target) { __externalVariable_Target = &__localVariable_Target; }
	if(*__externalVariable_Target) { free(*__externalVariable_Target); }

	*__externalVariable_Target = (char*)malloc(__localVariable_PrimarySize+__localVariable_SecondarySize);

	assert(*__externalVariable_Target);

	if(__localParameter_PrimaryLength) {
		assert(__localParameter_PrimarySource);

		for(__localVariable_Index=0;
			__localVariable_Index<__localParameter_PrimaryLength;
			__localVariable_Index++)
		{ (*__externalVariable_Target)[__localVariable_Index] = __localParameter_PrimarySource[__localVariable_Index]; }
	}

	if(__localParameter_SecondaryLength) {
		assert(__localParameter_SecondarySource);

		for(__localVariable_Index=0;
			__localVariable_Index<__localParameter_SecondaryLength;
			__localVariable_Index++)
		{ (*__externalVariable_Target)[__localParameter_PrimaryLength+__localVariable_Index] = __localParameter_SecondarySource[__localVariable_Index]; }
	}

	return *__externalVariable_Target;
}

char*
__ISSupport_RetrieveParameter(
	const int __localParameter_Limit,
	const char** __localParameter_Array,
	const char* __localParameter_Name,
	char** __externalVariable_Value)
{
	assert(__localParameter_Array);
	assert(__localParameter_Limit);
	assert(__localParameter_Name);

	bool __localVariable_Match = false;

	char __localVariable_Delimiter[1] = {'='};
	char __localVariable_Terminator[1] = {'\0'};
	char* __localVariable_Value = NULL;
	int __localVariable_Index = 0;

	if(!__externalVariable_Value) { __externalVariable_Value = &__localVariable_Value; }

	for(__localVariable_Index=0;
		__localVariable_Index<__localParameter_Limit&&
		!__localVariable_Match;
		__localVariable_Index++)
	{
		assert(__localParameter_Array[__localVariable_Index]);

		char* __localVariable_ParameterName = NULL;

		if(__ISSupport_SplitTerminatedCharArray(
			__localParameter_Array[__localVariable_Index],
			&__localVariable_ParameterName,
			__externalVariable_Value,
			__localVariable_Delimiter,
			__localVariable_Terminator,
			sizeof(__localVariable_Delimiter),
			sizeof(__localVariable_Terminator),
			__localVariable_Terminator,
			sizeof(__localVariable_Terminator)))
		{ if(strcasecmp(__localParameter_Name,__localVariable_ParameterName)==0) { __localVariable_Match = true; } }

		if(__localVariable_ParameterName) { free(__localVariable_ParameterName); }
	}

	if(!__localVariable_Match&&*__externalVariable_Value) {
		free(*__externalVariable_Value);
		*__externalVariable_Value = NULL; }

	return *__externalVariable_Value;
}

size_t
__ISSupport_RetrievePositionInCharArray(
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
				break; }
		}

		if(__localVariable_Matches) { break; }
	}

	return __localVariable_Index;
}

bool
__ISSupport_SplitTerminatedCharArray(
	const char* __localParameter_Source,
	char** __externalVariable_Start,
	char** __externalVariable_End,
	const char* __localParameter_Delimiters,
	const char* __localParameter_Terminators,
	const size_t __localParameter_DelimiterLength,
	const size_t __localParameter_TerminatorLength,
	const char* __localParameter_TerminatingSequence,
	const size_t __localParameter_TerminationSequenceLength)
{
	assert(__localParameter_DelimiterLength);
	assert(__localParameter_Delimiters);
	assert(__localParameter_Source);
	assert(__localParameter_TerminatingSequence);
	assert(__localParameter_TerminationSequenceLength);
	assert(__localParameter_TerminatorLength);
	assert(__localParameter_Terminators);
	assert(__externalVariable_End);
	assert(__externalVariable_Start);

	size_t __localVariable_StartLength = __ISSupport_RetrievePositionInCharArray(
		__localParameter_Source,
		__localParameter_Delimiters,
		__localParameter_DelimiterLength,
		(size_t)-1);

	size_t __localVariable_EndLength = __ISSupport_RetrievePositionInCharArray(
		&(__localParameter_Source[__localVariable_StartLength]),
		__localParameter_Terminators,
		__localParameter_TerminatorLength,
		(size_t)-1);

	if(__localVariable_EndLength>1) {
		assert(__ISSupport_CopyCharArray(
			&(__localParameter_Source[__localVariable_StartLength+1]),
			__localVariable_EndLength-1,
			__localParameter_TerminatingSequence,
			__localParameter_TerminationSequenceLength,
			__externalVariable_End)); }
	else if(*__externalVariable_End) {
		free(*__externalVariable_End);
		*__externalVariable_End = NULL; }

	if(__localVariable_StartLength) {
		assert(__ISSupport_CopyCharArray(
			__localParameter_Source,
			__localVariable_StartLength,
			__localParameter_TerminatingSequence,
			__localParameter_TerminationSequenceLength,
			__externalVariable_Start)); }
	else if(*__externalVariable_Start) {
		free(*__externalVariable_Start);
		*__externalVariable_Start = NULL; }
	
	if(*__externalVariable_Start&&*__externalVariable_End) { return true; }
	else { return false; }
}
