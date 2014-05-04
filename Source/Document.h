#ifndef __ISDEFINITION_DOCUMENT_HEADER
#define __ISDEFINITION_DOCUMENT_HEADER 4

#include "Miscellaneous.h"

#include <stdbool.h>
#include <stdio.h>

struct __ISStructure_DocumentNode {
	struct __ISStructure_MemoryBuffer Name;
	struct __ISStructure_MemoryBuffer Value;
	struct {
		__ISType_Value Size;
		struct __ISStructure_DocumentNode** Array;
	} Children;
	struct {
		struct __ISStructure_DocumentNode* Older;
		struct __ISStructure_DocumentNode* Younger;
	} Siblings;
	struct __ISStructure_DocumentNode* Parent;
};

#endif
