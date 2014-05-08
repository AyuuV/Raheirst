#ifndef __ISDEFINITION_PARSER_HEADER
#define __ISDEFINITION_PARSER_HEADER 3

#include "Document.h"
#include "Miscellaneous.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct __ISStructure_VariableItem {
	struct __ISStructure_MemoryBuffer* Name;
	struct __ISStructure_MemoryBuffer* Value;
};

struct __ISStructure_MemoryBuffer*
__ISFunction_ParseStream(
	FILE* __localParameter_Stream,
	struct __ISStructure_FIFOStackObject* __localParameter_Functions,
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	const char __localParameter_Terminator,
	const bool __localParameter_WhitespaceIgnorant);

void
__ISFunction_ParseStreamIgnoreComment(
	FILE* __localParameter_Stream,
	const char __localParameter_Terminator);

void
__ISFunction_ParseStreamReleaseVariable(
	struct __ISStructure_VariableItem* __localParameter_Variable);

struct __ISStructure_VariableItem*
__ISFunction_ParseStreamRetrieveVariable(
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	const struct __ISStructure_MemoryBuffer* __localParameter_Name);

#endif
