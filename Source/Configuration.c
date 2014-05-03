#include "Configuration.h"
#include "Miscellaneous.h"

#include <stdio.h>

#ifdef __CONFIGURATION_SOURCE_DEFINE_MAIN_DEFINITION

#define DEFINITION_CONFIGURATION_MAIN_ERROR -1
#define DEFINITION_CONFIGURATION_MAIN_SUCCESS 0
#define DEFINITION_CONFIGURATION_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	(void)__localParameter_ArgumentArray;
	(void)__localParameter_ArgumentLimit;

	__ISType_Time __localVariable_InitialTimeP = __ISFunction_RetrieveProcessorTime(1000000,0);
	__ISType_Time __localVariable_InitialTimeW = __ISFunction_RetrieveWallTime(0);

	fprintf(stdout,"Processor Time: %ju\nWall Time: %ju\n",__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeP),__ISFunction_RetrieveWallTime(__localVariable_InitialTimeW));

	return DEFINITION_CONFIGURATION_MAIN_SUCCESS;
}

#endif
