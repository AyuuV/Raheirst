#include "Miscellaneous.h"

#include <assert.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include <time.h>

struct __ISStructure_MemoryBuffer*
__ISFunction_CreateMemoryBufferFromArrays(
	const void* __localParameter_PrimaryArray,
	const void* __localParameter_SecondaryArray,
	const __ISType_Size __localParameter_PrimaryLength,
	const __ISType_Size __localParameter_SecondaryLength)
{
	__ISType_Size __localVariable_Index = 0;
	__ISType_Size __localVariable_PrimaryPosition = 0;
	__ISType_Size __localVariable_UnitSize = 0;
	struct __ISStructure_MemoryBuffer* __localVariable_ResultingMemoryBuffer = (struct __ISStructure_MemoryBuffer*)malloc(sizeof(*__localVariable_ResultingMemoryBuffer));
	assert(__localVariable_ResultingMemoryBuffer);
	__localVariable_PrimaryPosition = __localParameter_PrimaryLength/sizeof(*__localVariable_ResultingMemoryBuffer->Data);
	__localVariable_UnitSize = sizeof(*__localVariable_ResultingMemoryBuffer->Data);
	__localVariable_ResultingMemoryBuffer->Size = (__localParameter_PrimaryLength+__localParameter_SecondaryLength)/__localVariable_UnitSize;
	__localVariable_ResultingMemoryBuffer->Data = (__ISType_MemoryUnit*)malloc(__localVariable_ResultingMemoryBuffer->Size*__localVariable_UnitSize);
	__localVariable_ResultingMemoryBuffer->Next = NULL;
	__localVariable_ResultingMemoryBuffer->Previous = NULL;
	if(__localParameter_PrimaryLength&&__localParameter_PrimaryArray) {
		for(__localVariable_Index=0;
			__localVariable_Index<__localVariable_PrimaryPosition;
			__localVariable_Index++)
		{ __localVariable_ResultingMemoryBuffer->Data[__localVariable_Index] = ((__ISType_MemoryUnit*)__localParameter_PrimaryArray)[__localVariable_Index]; }
	}
	if(__localParameter_SecondaryLength&&__localParameter_SecondaryArray) {
		for(__localVariable_Index=0;
			__localVariable_Index<__localParameter_SecondaryLength/__localVariable_UnitSize;
			__localVariable_Index++)
		{ __localVariable_ResultingMemoryBuffer->Data[__localVariable_Index+__localVariable_PrimaryPosition] = ((__ISType_MemoryUnit*)__localParameter_SecondaryArray)[__localVariable_Index]; }
	}
	return __localVariable_ResultingMemoryBuffer;
}

struct __ISStructure_FIFOStackObject*
__ISFunction_PopFIFOStack(
	struct __ISStructure_FIFOStackObject* __localParameter_FIFOStack,
	void (*__externalFunction_Action)(void*))
{
	struct __ISStructure_FIFOStackObject* __localParameter_ResultingFIFOStack = NULL;
	if(__localParameter_FIFOStack) {
		if(__externalFunction_Action) { (*__externalFunction_Action)(__localParameter_FIFOStack->Object); }
		__localParameter_ResultingFIFOStack = __localParameter_FIFOStack->Previous; }
	return __localParameter_ResultingFIFOStack;
}

struct __ISStructure_FIFOStackObject*
__ISFunction_PushFIFOStack(
	struct __ISStructure_FIFOStackObject* __localParameter_FIFOStack,
	void* __localParameter_Object)
{
	struct __ISStructure_FIFOStackObject* __localVariable_NewFIFOStackObject = (struct __ISStructure_FIFOStackObject*)malloc(sizeof(*__localVariable_NewFIFOStackObject));
	assert(__localVariable_NewFIFOStackObject);
	__localVariable_NewFIFOStackObject->Object = __localParameter_Object;
	__localVariable_NewFIFOStackObject->Previous = __localParameter_FIFOStack;
	return __localVariable_NewFIFOStackObject;
}

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
	return ((__ISType_Time)((__localVariable_TimevalStructure.tv_sec*1000000)+__localVariable_TimevalStructure.tv_usec))-__localParameter_Offset;
}

bool
__ISFunction_WriteMemoryBufferToStream(
	FILE* __localParameter_Stream,
	const struct __ISStructure_MemoryBuffer* __localParameter_MemoryBuffer)
{
	if(!__localParameter_Stream) { return false; }
	struct __ISStructure_MemoryBuffer* __localVariable_CurrentMemoryBuffer = (struct __ISStructure_MemoryBuffer*)__localParameter_MemoryBuffer;
	while(__localVariable_CurrentMemoryBuffer->Previous) { __localVariable_CurrentMemoryBuffer = __localVariable_CurrentMemoryBuffer->Previous; }
	while(__localVariable_CurrentMemoryBuffer) {
		__ISType_Size __localVariable_Written = fwrite(
			__localVariable_CurrentMemoryBuffer->Data,
			sizeof(*__localVariable_CurrentMemoryBuffer->Data),
			__localVariable_CurrentMemoryBuffer->Size,
			__localParameter_Stream);
		if(__localVariable_Written!=__localVariable_CurrentMemoryBuffer->Size) { return false; }
		__localVariable_CurrentMemoryBuffer = __localVariable_CurrentMemoryBuffer->Next; }
	return true;
}
