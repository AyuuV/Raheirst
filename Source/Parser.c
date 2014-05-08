#include "Document.h"
#include "Miscellaneous.h"
#include "Parser.h"
#include "Support.h"

#include <assert.h>

#include <stdbool.h>
#include <stdio.h>

#include <string.h>

#ifdef __ISDEFINITION_PARSER_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_PARSER_MAIN_ERROR -1
#define __ISDEFINITION_PARSER_MAIN_SUCCESS 0
#define __ISDEFINITION_PARSER_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	char* __localVariable_Terminator = __ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit,
		__localParameter_ArgumentArray,
		"TERMINATOR",
		NULL);
	if(!__localVariable_Terminator) { __localVariable_Terminator = ""; }

	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = NULL;
	struct __ISStructure_FIFOStackObject* __localVariable_Functions = NULL;
	struct __ISStructure_FIFOStackObject* __localVariable_Variables = NULL;

	while((__localVariable_MemoryBuffer=__ISFunction_ParseStream(
		stdin,
		__localVariable_Functions,
		__localVariable_Variables,
		__localVariable_Terminator[0])))
	{
		__ISFunction_WriteMemoryBufferToStream(
			stdout,
			__localVariable_MemoryBuffer);
	}

	return __ISDEFINITION_PARSER_MAIN_SUCCESS;
}

#endif

struct __ISStructure_MemoryBuffer*
__ISFunction_ParseStream(
	FILE* __localParameter_Stream,
	struct __ISStructure_FIFOStackObject* __localParameter_Functions,
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	const char __localParameter_Terminator)
{
	bool __localVariable_ParseStream = true;
	char __localVariable_Character = '\0';
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = NULL;
	__localParameter_Functions = __ISFunction_PushFIFOStack(
		__localParameter_Functions,
		NULL);
	__localParameter_Variables = __ISFunction_PushFIFOStack(
		__localParameter_Variables,
		NULL);

	assert(__localParameter_Functions);
	assert(__localParameter_Variables);

	while(__localVariable_ParseStream&&fread(&__localVariable_Character,1,1,__localParameter_Stream)==1&&
		__localVariable_Character!=__localParameter_Terminator)
	{
		switch(__localVariable_Character) {
			case('\\'): { if(fread(&__localVariable_Character,1,1,__localParameter_Stream)!=1) {
				__localParameter_Stream = false;
				break; } }
			default: {
				struct __ISStructure_MemoryBuffer* __localVariable_Temporary_MemoryBuffer = __ISFunction_CreateMemoryBufferFromArrays(
					&(__localVariable_Character),
					NULL,
					1,
					0);
				__ISFunction_AppendMemoryBuffer(
					__localVariable_MemoryBuffer,
					__localVariable_Temporary_MemoryBuffer);
				__localVariable_MemoryBuffer = __localVariable_Temporary_MemoryBuffer;
				break; }
		}
	}

	__ISFunction_ReleaseFIFOStack(
		__localParameter_Functions->Object,
		free);
	__ISFunction_ReleaseFIFOStack(
		__localParameter_Variables->Object,
		free);
	__ISFunction_PopFIFOStack(
		__localParameter_Functions,
		NULL);
	__ISFunction_PopFIFOStack(
		__localParameter_Variables,
		NULL);
	return __localVariable_MemoryBuffer;
}
