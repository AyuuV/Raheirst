#include "Parser.h"
#include "Miscellaneous.h"

#include <assert.h>

#include <stdbool.h>
#include <stdio.h>

#ifdef __ISDEFINITION_PARSER_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_PARSER_MAIN_ERROR -1
#define __ISDEFINITION_PARSER_MAIN_SUCCESS 0
#define __ISDEFINITION_PARSER_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	(void)__localParameter_ArgumentArray;
	(void)__localParameter_ArgumentLimit;

	struct __ISStructure_FIFOStackObject* __localVariable_Variables = NULL;
	struct __ISStructure_ParseConfiguration __localVariable_Configuration;

	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = __ISFunction_ParseStream(
		stdin,
		__localVariable_Variables,
		&__localVariable_Configuration);

	assert(__localVariable_MemoryBuffer);

	assert(__ISFunction_WriteMemoryBufferToStream(
		stdout,
		__localVariable_MemoryBuffer));

	return __ISDEFINITION_PARSER_MAIN_SUCCESS;
}

#endif

struct __ISStructure_MemoryBuffer*
__ISFunction_ParseStream(
	FILE* __localParameter_Stream,
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	struct __ISStructure_ParseConfiguration* __localParameter_Configuration)
{
	assert(__localParameter_Stream);

	__ISType_MemoryUnit __localVariable_Current = 0;
	__ISType_Size __localVariable_Index = 0;
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = NULL;
	struct __ISStructure_DictionaryNode* __localVariable_NewDictionary = (struct __ISStructure_DictionaryNode*)malloc(sizeof(*__localVariable_NewDictionary));

	assert(__localVariable_NewDictionary);
	__localVariable_NewDictionary->Data = NULL;
	for(__localVariable_Index=0;
		__localVariable_Index<__ISDEFINITION_MEMORYUNIT_SIZE;
		__localVariable_Index++)
	{ __localVariable_NewDictionary->KeyArray[__localVariable_Index] = NULL; }

	__localParameter_Variables = __ISFunction_PushFIFOStack(
		__localParameter_Variables,
		__localVariable_NewDictionary);

	while(fread(&__localVariable_Current,sizeof(__localVariable_Current),1,__localParameter_Stream)==1) {
		// Stuff
	}

	return __localVariable_MemoryBuffer;
}
