#ifndef __ISDEFINITION_PARSER_HEADER
#define __ISDEFINITION_PARSER_HEADER 3

#include "Document.h"
#include "Miscellaneous.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct __ISStructure_MemoryBuffer*
__ISFunction_ParseStream(
	FILE* __localParameter_Stream,
	struct __ISStructure_FIFOStackObject* __localParameter_Functions,
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	const char __localParameter_Terminator);

#endif
