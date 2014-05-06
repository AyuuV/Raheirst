#include "Document.h"
#include "Miscellaneous.h"
#include "Support.h"

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <strings.h>

#ifdef __ISDEFINITION_DOCUMENT_SOURCE_DEFINE_MAIN

#define __ISDEFINITION_DOCUMENT_MAIN_ERROR -1
#define __ISDEFINITION_DOCUMENT_MAIN_SUCCESS 0
#define __ISDEFINITION_DOCUMENT_MAIN_FAILURE 1

int main(
	const int __localParameter_ArgumentLimit,
	const char** __localParameter_ArgumentArray)
{
	__ISType_Time __localVariable_InitialTimeProcess = __ISFunction_RetrieveProcessorTime(1000000,0);
	__ISType_Time __localVariable_InitialTimeWall = __ISFunction_RetrieveWallTime(0);

	char* __localVariable_Acknowledgement = __ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit-1,
		&(__localParameter_ArgumentArray[1]),
		"ACKNOWLEDGEMENT",
		NULL);

	char* __localVariable_TimerMode = __ISSupport_RetrieveParameter(
		__localParameter_ArgumentLimit-1,
		&(__localParameter_ArgumentArray[1]),
		"TIMER",
		NULL);

	if(__localVariable_Acknowledgement) {
		fprintf(stderr,"%s\n",__localVariable_Acknowledgement);
		free(__localVariable_Acknowledgement); }

	// Stuff

	if(__localVariable_TimerMode) {
		if(strcasecmp(__localVariable_TimerMode,"WALL")==0) { fprintf(stderr,"Program Wall Microseconds: %ju\n",__ISFunction_RetrieveWallTime(__localVariable_InitialTimeWall)); }
		else if(strcasecmp(__localVariable_TimerMode,"PROCESS")==0) { fprintf(stderr,"Program Process Microseconds: %ju\n",__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeProcess)); }
		else if(strcasecmp(__localVariable_TimerMode,"BOTH")==0) {
			 fprintf(
				stderr,
				"Program Process Microseconds: %ju\nProgram Wall Microseconds: %ju\n",
				__ISFunction_RetrieveProcessorTime(1000000,__localVariable_InitialTimeProcess),
				__ISFunction_RetrieveWallTime(__localVariable_InitialTimeWall));
		}
		free(__localVariable_TimerMode); }
	return __ISDEFINITION_DOCUMENT_MAIN_SUCCESS;
}

#endif

struct __ISStructure_DocumentNode*
__ISFunction_InsertDocumentNode(
	struct __ISStructure_DocumentNode* __localParameter_Parent,
	struct __ISStructure_DocumentNode* __localParameter_SiblingNode,
	struct __ISStructure_MemoryBuffer* __localParameter_NodeName,
	struct __ISStructure_MemoryBuffer* __localParameter_NodeValue,
	bool __localParameter_Append)
{
	struct __ISStructure_DocumentNode* __localVariable_Node = malloc(sizeof(*__localVariable_Node));
	assert(__localVariable_Node);

	if(__localParameter_SiblingNode) { assert(__localParameter_SiblingNode->Parent==__localParameter_Parent); }

	__localVariable_Node->Children.Oldest = NULL;
	__localVariable_Node->Children.Youngest = NULL;
	__localVariable_Node->Parent = __localParameter_Parent;

	__localVariable_Node->Name = __ISFunction_CollateMemoryBuffers(__localParameter_NodeName,NULL);
	__localVariable_Node->Value = __ISFunction_CollateMemoryBuffers(__localParameter_NodeValue,NULL);

	if(__localParameter_Append) {
		__localVariable_Node->Siblings.Older = __localParameter_SiblingNode;
		__localVariable_Node->Siblings.Younger = NULL;
		if(__localParameter_SiblingNode) {
			if(__localParameter_SiblingNode->Siblings.Younger) {
				__localVariable_Node->Siblings.Younger = __localParameter_SiblingNode->Siblings.Younger;
				__localParameter_SiblingNode->Siblings.Younger->Siblings.Older = __localVariable_Node; }
			if(__localParameter_Parent&&__localParameter_Parent->Children.Youngest==__localParameter_SiblingNode) { __localParameter_Parent->Children.Youngest = __localVariable_Node; }
			__localParameter_SiblingNode->Siblings.Younger = __localVariable_Node; }
		else {
			if(!__localParameter_Parent->Children.Oldest) { __localParameter_Parent->Children.Oldest = __localVariable_Node; }
			__localParameter_Parent->Children.Youngest = __localVariable_Node; } }
	else {
		__localVariable_Node->Siblings.Older = NULL;
		__localVariable_Node->Siblings.Younger = __localParameter_SiblingNode;
		if(__localParameter_SiblingNode) {
			if(__localParameter_SiblingNode->Siblings.Older) {
				__localVariable_Node->Siblings.Older = __localParameter_SiblingNode->Siblings.Older;
				__localParameter_SiblingNode->Siblings.Older->Siblings.Younger = __localVariable_Node; }
			if(__localParameter_Parent&&__localParameter_Parent->Children.Oldest==__localParameter_SiblingNode) { __localParameter_Parent->Children.Oldest = __localVariable_Node; }
			__localParameter_SiblingNode->Siblings.Older = __localVariable_Node; }
		else {
			if(!__localParameter_Parent->Children.Youngest) { __localParameter_Parent->Children.Youngest = __localVariable_Node; }
			__localParameter_Parent->Children.Oldest = __localVariable_Node; } }

	return __localVariable_Node;
}
