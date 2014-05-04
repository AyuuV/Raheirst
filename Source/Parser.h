#ifndef __ISDEFINITION_PARSER_HEADER
#define __ISDEFINITION_PARSER_HEADER 3

#include "Miscellaneous.h"

#include <stdio.h>
#include <stdlib.h>

struct __ISStructure_ParseConfiguration {
	struct {

	};
};

struct __ISStructure_MemoryBuffer*
__ISFunction_ParseStream(
	FILE* __localParameter_Stream,
	struct __ISStructure_FIFOStackObject* __localParameter_Variables,
	struct __ISStructure_ParseConfiguration* __localParameter_Configuration);

#endif
