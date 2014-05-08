#include "Miscellaneous.h"

#include <assert.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include <time.h>

struct __ISStructure_MemoryBuffer*
__ISFunction_AppendMemoryBuffer(
	struct __ISStructure_MemoryBuffer* __localParameter_Primary,
	struct __ISStructure_MemoryBuffer* __localParameter_Secondary)
{
	struct __ISStructure_MemoryBuffer* __localVariable_Primary = __localParameter_Primary;
	struct __ISStructure_MemoryBuffer* __localVariable_Secondary = __localParameter_Secondary;
	while(__localVariable_Primary&&__localVariable_Primary->Next) { __localVariable_Primary = __localVariable_Primary->Next; }
	while(__localVariable_Secondary&&__localVariable_Secondary->Previous) { __localVariable_Secondary = __localVariable_Secondary->Previous; }
	if(__localVariable_Primary) { __localVariable_Primary->Next = __localVariable_Secondary; }
	if(__localVariable_Secondary) { __localVariable_Secondary->Previous = __localVariable_Primary; }
	if(__localVariable_Primary) { return __localParameter_Primary; }
	else { return __localVariable_Secondary; }
}

struct __ISStructure_MemoryBuffer*
__ISFunction_CollateMemoryBuffers(
	const struct __ISStructure_MemoryBuffer* __localParameter_Primary,
	const struct __ISStructure_MemoryBuffer* __localParameter_Secondary)
{
	__ISType_Size __localVariable_Index = 0;
	__ISType_Size __localVariable_PrimarySize = __ISFunction_RetrieveMemoryBufferLength(__localParameter_Primary,NULL);
	__ISType_Size __localVariable_SecondarySize = __ISFunction_RetrieveMemoryBufferLength(__localParameter_Secondary,NULL);
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = (struct __ISStructure_MemoryBuffer*)malloc(sizeof(*__localVariable_MemoryBuffer));
	assert(__localVariable_MemoryBuffer);
	__localVariable_MemoryBuffer->Next = NULL;
	__localVariable_MemoryBuffer->Previous = NULL;
	if((__localVariable_MemoryBuffer->Size=__localVariable_PrimarySize+__localVariable_SecondarySize)) {
		__localVariable_MemoryBuffer->Data = (__ISType_MemoryUnit*)malloc(__localVariable_MemoryBuffer->Size);
		assert(__localVariable_MemoryBuffer->Data);
		__ISType_Size __localVariable_TotalIndex = 0;
		struct __ISStructure_MemoryBuffer* __localVariable_TargetMemoryBuffer = NULL;
		if(__localVariable_PrimarySize&&__localParameter_Primary) {
			__localVariable_TargetMemoryBuffer = (struct __ISStructure_MemoryBuffer*)__localParameter_Primary;
			while(__localVariable_TargetMemoryBuffer->Previous) { __localVariable_TargetMemoryBuffer = __localVariable_TargetMemoryBuffer->Previous; }
			while(__localVariable_TargetMemoryBuffer) {
				for(__localVariable_Index=0;
					__localVariable_Index<__localVariable_TargetMemoryBuffer->Size;
					__localVariable_Index++,
					__localVariable_TotalIndex++)
				{ __localVariable_MemoryBuffer->Data[__localVariable_TotalIndex] = __localVariable_TargetMemoryBuffer->Data[__localVariable_Index]; }
				__localVariable_TargetMemoryBuffer = __localVariable_TargetMemoryBuffer->Next; } }
		if(__localVariable_SecondarySize&&__localParameter_Secondary) {
			__localVariable_TargetMemoryBuffer = (struct __ISStructure_MemoryBuffer*)__localParameter_Secondary;
			while(__localVariable_TargetMemoryBuffer->Previous) { __localVariable_TargetMemoryBuffer = __localVariable_TargetMemoryBuffer->Previous; }
			while(__localVariable_TargetMemoryBuffer) {
				for(__localVariable_Index=0;
					__localVariable_Index<__localVariable_TargetMemoryBuffer->Size;
					__localVariable_Index++,
					__localVariable_TotalIndex++)
				{ __localVariable_MemoryBuffer->Data[__localVariable_TotalIndex] = __localVariable_TargetMemoryBuffer->Data[__localVariable_Index]; }
				__localVariable_TargetMemoryBuffer = __localVariable_TargetMemoryBuffer->Next; } }
	}
	else { __localVariable_MemoryBuffer->Data = NULL; }
	return __localVariable_MemoryBuffer;
}

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

bool
__ISFunction_MatchMemoryBuffers(
	const struct __ISStructure_MemoryBuffer* __localParameter_Primary,
	const struct __ISStructure_MemoryBuffer* __localParameter_Secondary)
{
	__ISType_Size __localVariable_Index = 0;
	struct __ISStructure_MemoryBuffer* __localVariable_Primary = (struct __ISStructure_MemoryBuffer*)__localParameter_Primary;
	struct __ISStructure_MemoryBuffer* __localVariable_Secondary = (struct __ISStructure_MemoryBuffer*)__localParameter_Secondary;
	while(__localVariable_Primary->Previous) {__localVariable_Primary = __localVariable_Primary->Previous; }
	while(__localVariable_Secondary->Previous) {__localVariable_Secondary = __localVariable_Secondary->Previous; }
	if(__localVariable_Primary==__localVariable_Secondary) { return true; }
	if(!__localVariable_Primary) { return false; }
	while(__localVariable_Primary) {
		if(!__localVariable_Secondary) { return false; }
		if(__localVariable_Primary->Size!=__localVariable_Secondary->Size) { return false; }
		for(__localVariable_Index=0;
			__localVariable_Index<__localVariable_Primary->Size;
			__localVariable_Index++)
		{ if(__localVariable_Primary->Data[__localVariable_Index]!=__localVariable_Secondary->Data[__localVariable_Index]) { return false; } }
		__localVariable_Primary = __localVariable_Primary->Next;
		__localVariable_Secondary = __localVariable_Secondary->Next;
		if((__localVariable_Primary&&__localVariable_Secondary)!=(__localVariable_Primary||__localVariable_Secondary)) { return false; } }
	return true;
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

void
__ISFunction_ReleaseFIFOStack(
	struct __ISStructure_FIFOStackObject* __localParameter_FIFOStack,
	void (*__externalFunction_ReleaseAction)(void*))
{
	struct __ISStructure_FIFOStackObject* __localParameter_TargetFIFOStack = NULL;
	while(__localParameter_FIFOStack) {
		if(__externalFunction_ReleaseAction&&__localParameter_FIFOStack->Object) { __externalFunction_ReleaseAction(__localParameter_FIFOStack->Object); }
		__localParameter_TargetFIFOStack = __localParameter_FIFOStack;
		__localParameter_FIFOStack = __localParameter_FIFOStack->Previous;
		free(__localParameter_TargetFIFOStack); }
	return;
}

void
__ISFunction_ReleaseMemoryBuffer(
	struct __ISStructure_MemoryBuffer* __localParameter_MemoryBuffer,
	const bool __localParameter_ReleaseAll)
{
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = __localParameter_MemoryBuffer;
	if(__localParameter_ReleaseAll) {
		struct __ISStructure_MemoryBuffer* __localVariable_OldMemoryBuffer = NULL;
		while(__localVariable_MemoryBuffer->Previous) { __localVariable_MemoryBuffer = __localVariable_MemoryBuffer->Previous; }
		while(__localVariable_MemoryBuffer) {
			if(__localVariable_MemoryBuffer->Data) { free(__localVariable_MemoryBuffer->Data); }
			__localVariable_OldMemoryBuffer = __localVariable_MemoryBuffer;
			__localVariable_MemoryBuffer = __localVariable_MemoryBuffer->Next;
			free(__localVariable_OldMemoryBuffer); } }
	else if(__localParameter_MemoryBuffer) {
		if(__localVariable_MemoryBuffer->Data) { free(__localVariable_MemoryBuffer->Data); }
		if(__localVariable_MemoryBuffer->Next) { __localVariable_MemoryBuffer->Next->Previous = __localVariable_MemoryBuffer->Previous; }
		if(__localVariable_MemoryBuffer->Previous) { __localVariable_MemoryBuffer->Previous->Next = __localVariable_MemoryBuffer->Next; }
		free(__localVariable_MemoryBuffer); }
	return;
}

__ISType_Size
__ISFunction_RetrieveMemoryBufferLength(
	const struct __ISStructure_MemoryBuffer* __localParameter_MemoryBuffer,
	__ISType_Size* __localParameter_MemoryBuffers)
{
	__ISType_Size __localVariable_Length = 0;
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = (struct __ISStructure_MemoryBuffer*)__localParameter_MemoryBuffer;
	while(__localVariable_MemoryBuffer&&__localVariable_MemoryBuffer->Previous) { __localVariable_MemoryBuffer = __localVariable_MemoryBuffer->Previous; }
	if(__localParameter_MemoryBuffers) { *__localParameter_MemoryBuffers = 0; }
	if(__localVariable_MemoryBuffer) {
		for(__localVariable_Length=0;
			__localVariable_MemoryBuffer;
			__localVariable_Length+=__localVariable_MemoryBuffer->Size,
			__localVariable_MemoryBuffer=__localVariable_MemoryBuffer->Next)
		{ if(__localParameter_MemoryBuffers) { (*__localParameter_MemoryBuffers)++; } }
	}
	return __localVariable_Length;
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

struct __ISStructure_MemoryBuffer*
__ISFunction_RetrieveStreamSegmentIntoMemoryBuffer(
	FILE* __localParameter_Stream,
	const struct __ISStructure_MemoryBuffer* __localParameter_TerminatingSequence,
	const __ISType_Size __localParameter_MaximumSegmentSize)
{
	__ISType_Size __localVariable_ComparisionIndex = 0;
	__ISType_Size __localVariable_Index = 0;
	__ISType_Size __localVariable_ReadSize = 0;
	__ISType_Size __localVariable_UnitSize = sizeof(__ISType_MemoryUnit);
	struct __ISStructure_MemoryBuffer* __localVariable_InitialMemoryBuffer = NULL;
	struct __ISStructure_MemoryBuffer* __localVariable_InitialTerminatingSequence = (struct __ISStructure_MemoryBuffer*)__localParameter_TerminatingSequence;
	struct __ISStructure_MemoryBuffer* __localVariable_MemoryBuffer = NULL;
	struct __ISStructure_MemoryBuffer* __localVariable_TerminatingSequence = NULL;
	while(__localVariable_InitialTerminatingSequence->Previous) { __localVariable_InitialTerminatingSequence = __localVariable_InitialTerminatingSequence->Previous; }
	__localVariable_TerminatingSequence = __localVariable_InitialTerminatingSequence;

	for(__localVariable_Index=0;
		__localVariable_Index<__localParameter_MaximumSegmentSize;
		__localVariable_Index++)
	{
		struct __ISStructure_MemoryBuffer* __localVariable_NewMemoryBuffer = (struct __ISStructure_MemoryBuffer*)malloc(sizeof(*__localVariable_MemoryBuffer));

		assert(__localVariable_NewMemoryBuffer);

		__localVariable_NewMemoryBuffer->Data = NULL;
		__localVariable_NewMemoryBuffer->Next = NULL;
		__localVariable_NewMemoryBuffer->Previous = __localVariable_MemoryBuffer;
		__localVariable_NewMemoryBuffer->Size = __localVariable_UnitSize;

		if(__localVariable_MemoryBuffer) { __localVariable_MemoryBuffer->Next = __localVariable_NewMemoryBuffer; }
		else { __localVariable_InitialMemoryBuffer = __localVariable_NewMemoryBuffer; }

		__localVariable_MemoryBuffer = __localVariable_NewMemoryBuffer;

		__localVariable_ReadSize = fread(
			&__localVariable_MemoryBuffer->Data,
			__localVariable_UnitSize,
			1,
			__localParameter_Stream);
		assert(__localVariable_ReadSize);
		assert(ferror(__localParameter_Stream)==0);

		if(__localVariable_TerminatingSequence&&__localVariable_TerminatingSequence->Data) {
			if(__localVariable_TerminatingSequence->Data[__localVariable_ComparisionIndex++]==__localVariable_MemoryBuffer->Data[0]) {
				if(!(__localVariable_ComparisionIndex<__localVariable_TerminatingSequence->Size)) {
					if(__localVariable_TerminatingSequence->Next) {
						__localVariable_TerminatingSequence = __localVariable_TerminatingSequence->Next;
						__localVariable_ComparisionIndex = 0; }
					else { break; } } }
			else {
				__localVariable_TerminatingSequence = __localVariable_InitialTerminatingSequence;
				__localVariable_ComparisionIndex = 0; } }

	}

	return __localVariable_InitialMemoryBuffer;
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
