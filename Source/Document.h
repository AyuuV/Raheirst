#ifndef __ISDEFINITION_DOCUMENT_HEADER
#define __ISDEFINITION_DOCUMENT_HEADER 5

#include "Miscellaneous.h"

#include <stdbool.h>
#include <stdio.h>

struct __ISStructure_DocumentNode {
	struct __ISStructure_MemoryBuffer* Name;
	struct __ISStructure_MemoryBuffer* Value;
	struct {
		struct __ISStructure_DocumentNode* Oldest;
		struct __ISStructure_DocumentNode* Youngest;
	} Children;
	struct {
		struct __ISStructure_DocumentNode* Older;
		struct __ISStructure_DocumentNode* Younger;
	} Siblings;
	struct __ISStructure_DocumentNode* Parent;
};

struct __ISStructure_DocumentNode*
__ISFunction_InsertDocumentNode(
	struct __ISStructure_DocumentNode* __localParameter_Parent,
	struct __ISStructure_DocumentNode* __localParameter_SiblingNode,
	struct __ISStructure_MemoryBuffer* __localParameter_NodeName,
	struct __ISStructure_MemoryBuffer* __localParameter_NodeValue,
	bool __localParameter_Append);

#endif
