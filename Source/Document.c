#include "Document.h"
#include "Miscellaneous.h"
#include "Support.h"

#include <stdio.h>
#include <stdlib.h>

#include <strings.h>

#ifdef __ISDEFINITION_DOCUMENT_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_DOCUMENT_MAIN_ERROR -1
#define __ISDEFINITION_DOCUMENT_MAIN_SUCCESS 0
#define __ISDEFINITION_DOCUMENT_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	__ISType_Time __localVariable_InitialTimeProcess = __ISFunction_RetrieveProcessorTime(1000000,0);
	__ISType_Time __localVariable_InitialTimeWall = __ISFunction_RetrieveWallTime(0);

	char* __localVariable_Acknowledgement = __ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit-1,
		&(__localParameter_ArgumentArray[1]),
		"ACKNOWLEDGEMENT",
		NULL);

	char* __localVariable_TimerMode = __ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit-1,
		&(__localParameter_ArgumentArray[1]),
		"TIMER",
		NULL);

	if(__localVariable_Acknowledgement) {
		fprintf(stderr,"%s\n",__localVariable_Acknowledgement);
		free(__localVariable_Acknowledgement); }

	// Stuff

	if(__localVariable_TimerMode) {
		if(strcasecmp(__localVariable_TimerMode,"WALL")==0) { fprintf(stderr,"Program Wall Microseconds: %ju\n",__ISFunction_RetrieveWallTime(__localVariable_InitialTimeWall)); }
		else if(strcasecmp(__localVariable_TimerMode,"PROCESS")==0) { fprintf(stderr,"Program Process Microseconds: %ju\n",__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeProcess)); }
		else if(strcasecmp(__localVariable_TimerMode,"BOTH")==0) {
			 fprintf(
				stderr,
				"Program Process Microseconds: %ju\nProgram Wall Microseconds: %ju\n",
				__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeProcess),
				__ISFunction_RetrieveWallTime(__localVariable_InitialTimeWall));
		}
		free(__localVariable_TimerMode); }
	return __ISDEFINITION_DOCUMENT_MAIN_SUCCESS;
}

#endif
