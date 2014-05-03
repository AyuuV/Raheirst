#include "Miscellaneous.h"

#include <assert.h>

#include <stdint.h>
#include <stdlib.h>

#include <sys/time.h>

#include <time.h>

__ISType_Time
__ISFunction_RetrieveProcessorTime(
	const __ISType_Time __localParameter_Resolution,
	const __ISType_Time __localParameter_Offset)
{
	clock_t __localVariable_RetrievedTime = clock();
	assert(__localVariable_RetrievedTime>=0);
	return ((__localVariable_RetrievedTime*__localParameter_Resolution)/CLOCKS_PER_SEC)-__localParameter_Offset;
}

__ISType_Time
__ISFunction_RetrieveWallTime(
	const __ISType_Time __localParameter_Offset)
{
	struct timeval __localVariable_TimevalStructure;
	assert(!gettimeofday(&__localVariable_TimevalStructure,NULL));
	return ((__localVariable_TimevalStructure.tv_sec*1000000)+__localVariable_TimevalStructure.tv_usec)-__localParameter_Offset;
}
