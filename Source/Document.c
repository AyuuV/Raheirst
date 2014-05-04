#include "Document.h"
#include "Miscellaneous.h"
#include "Support.h"

#include <stdio.h>

#ifdef __ISDEFINITION_DOCUMENT_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_DOCUMENT_MAIN_ERROR -1
#define __ISDEFINITION_DOCUMENT_MAIN_SUCCESS 0
#define __ISDEFINITION_DOCUMENT_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	__ISType_Time __localVariable_InitialTimeP = __ISFunction_RetrieveProcessorTime(1000000,0);
	__ISType_Time __localVariable_InitialTimeW = __ISFunction_RetrieveWallTime(0);

	fprintf(stdout,"%s\n",__ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit-1,
		&(__localParameter_ArgumentArray[1]),
		"FILE",
		NULL));

	fprintf(stdout,"Processor Time: %ju\nWall Time: %ju\n",__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeP),__ISFunction_RetrieveWallTime(__localVariable_InitialTimeW));
	return __ISDEFINITION_DOCUMENT_MAIN_SUCCESS;
}

#endif
