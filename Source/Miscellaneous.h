#ifndef __ISDEFINITION_MISCELLANEOUS_HEADER
#define __ISDEFINITION_MISCELLANEOUS_HEADER 1

#include <limits.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define __ISDEFINITION_MEMORYUNIT_SIZE UCHAR_MAX

typedef unsigned char __ISType_MemoryUnit;

typedef intmax_t __ISType_Number;
typedef uintmax_t __ISType_Value;

typedef size_t __ISType_Size;
typedef uintmax_t __ISType_Time;

struct __ISStructure_DictionaryNode {
	void* Data;
	struct __ISStructure_DictionaryNode* KeyArray[__ISDEFINITION_MEMORYUNIT_SIZE];
};

struct __ISStructure_FIFOStackObject {
	void* Object;
	struct __ISStructure_FIFOStackObject* Previous;
};

struct __ISStructure_MemoryBuffer {
	__ISType_MemoryUnit* Data;
	struct __ISStructure_MemoryBuffer* Next;
	struct __ISStructure_MemoryBuffer* Previous;
	__ISType_Size Size;
};

struct __ISStructure_MemoryBuffer*
__ISFunction_AppendMemoryBuffer(
	struct __ISStructure_MemoryBuffer* __localParameter_Primary,
	struct __ISStructure_MemoryBuffer* __localParameter_Secondary);

struct __ISStructure_MemoryBuffer*
__ISFunction_CollateMemoryBuffers(
	const struct __ISStructure_MemoryBuffer* __localParameter_Primary,
	const struct __ISStructure_MemoryBuffer* __localParameter_Secondary);

struct __ISStructure_MemoryBuffer*
__ISFunction_CreateMemoryBufferFromArrays(
	const void* __localParameter_PrimaryArray,
	const void* __localParameter_SecondaryArray,
	const __ISType_Size __localParameter_PrimaryLength,
	const __ISType_Size __localParameter_SecondaryLength);

struct __ISStructure_FIFOStackObject*
__ISFunction_PopFIFOStack(
	struct __ISStructure_FIFOStackObject* __localParameter_FIFOStack,
	void (*__externalFunction_Action)(void*));

struct __ISStructure_FIFOStackObject*
__ISFunction_PushFIFOStack(
	struct __ISStructure_FIFOStackObject* __localParameter_FIFOStack,
	void* __localParameter_Object);

__ISType_Size
__ISFunction_RetrieveMemoryBufferLength(
	const struct __ISStructure_MemoryBuffer* __localParameter_MemoryBuffer,
	__ISType_Size* __localParameter_MemoryBuffers);

__ISType_Time
__ISFunction_RetrieveProcessorTime(
	const __ISType_Time __localParameter_Resolution,
	const __ISType_Time __localParameter_Offset);

__ISType_Time
__ISFunction_RetrieveWallTime(
	const __ISType_Time __localParameter_Offset);

bool
__ISFunction_WriteMemoryBufferToStream(
	FILE* __localParameter_Stream,
	const struct __ISStructure_MemoryBuffer* __localParameter_MemoryBuffer);

#endif
