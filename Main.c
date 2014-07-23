// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Main.c

#include "Definition.h"

#include "Config.h"
#include "Document.h"

#include <limits.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <strings.h>

int __argumentCount;
char** __argumentArray;

char*
getParameter(
	const char* parameterName,
	char* defaultValue,
	const int skip)
{
	char* delimiterPosition = NULL;
	char* parameterValue = NULL;
	int count = 0x00;
	int index = 0x00;

	for(index=0x00;
		index<__argumentCount;
		index++)
	{
		if(!(delimiterPosition=strchr(__argumentArray[index],'='))) { continue; }
		if(strlen(parameterName)!=(size_t)(delimiterPosition-__argumentArray[index])) { continue; }
		if(strncasecmp(__argumentArray[index],parameterName,delimiterPosition-__argumentArray[index])==0x00) {
			if(count==skip) {
				parameterValue = delimiterPosition+0x01;
				break; }
			else { count++; } }
	}

	if(!parameterValue) { return defaultValue; }
	else { return parameterValue; }
}

int main(
	int _argumentCount,
	char** _argumentArray)
{
	__argumentArray = _argumentArray;
	__argumentCount = _argumentCount;

	/*
	char* documentFilename = NULL;
	char* parameterValue = NULL;

	int parameterIndex = 0x00;

	enum FLM_Function functionValue = FLM_FunctionSuccess;

	struct FLM_Document* mainDocument = NULL;
	if((functionValue=FLM_NewDocument(&mainDocument))!=FLM_FunctionSuccess) {
		fprintf(stderr,"Failed to initialise main document: %d\n",(int)functionValue);
		abort(); }

	if((parameterValue=getParameter("version",NULL,0x00))) {
		if(strcasecmp(parameterValue,"display")==0x00) { fprintf(stdout,"[ **** Rainbow Heart ~ Iris Star **** ]\n --= Flowering Love Maiden =-- \nVersion 0.0.1\n"); }
		else if(strcasecmp(parameterValue,"string")==0x00) { fprintf(stdout,"version 0.0.1\n"); }
		else if(strcasecmp(parameterValue,"value")==0x00) { fprintf(stdout,"0.0.1\n"); }
		else {
			fprintf(stderr,"Invalid Version Display Mode %s\n",parameterValue);
			abort(); } }

	while((documentFilename=getParameter("format",NULL,parameterIndex)))
	{
		if((parameterValue=getParameter("blocklimit",NULL,parameterIndex))) { mainDocument->blockInformation->blockLimit = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->blockInformation->blockLimit = -0x01; }
		if((parameterValue=getParameter("blocksize",NULL,parameterIndex))) { mainDocument->blockInformation->blockSize = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->blockInformation->blockSize = 0x10; }
		if((parameterValue=getParameter("indexsize",NULL,parameterIndex))) { mainDocument->blockInformation->indexEntrySize = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->blockInformation->indexEntrySize = 0x80; }
		if((parameterValue=getParameter("datalimit",NULL,parameterIndex))) { mainDocument->data->limit = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->data->limit = -0x01; }
		if((parameterValue=getParameter("dataoffset",NULL,parameterIndex))) { mainDocument->data->offset = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->data->offset = 0xFF; }
		if((parameterValue=getParameter("indexlimit",NULL,parameterIndex))) { mainDocument->index->limit = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->index->limit = -0x01; }
		if((parameterValue=getParameter("indexoffset",NULL,parameterIndex))) { mainDocument->index->offset = strtoul(parameterValue,NULL,0x00); }
		else { mainDocument->index->offset = 0xFF; }

		mainDocument->data->filename = getParameter("datafile","data.datafile",parameterIndex);
		mainDocument->index->filename = getParameter("indexfile","index.datafile",parameterIndex);

		if((functionValue=FLM_WriteDocumentInformation(mainDocument,documentFilename,0x00))!=FLM_FunctionSuccess) {
			fprintf(stderr,"Failed to write document %s information: %d\n",documentFilename,(int)functionValue);
			abort(); }

		mainDocument->data->filename = NULL;
		mainDocument->index->filename = NULL;

		parameterIndex++;
	}

	parameterIndex = 0x00;

	while((documentFilename=getParameter("document",NULL,parameterIndex)))
	{
		if(!mainDocument) {
			if((functionValue=FLM_NewDocument(&mainDocument))!=FLM_FunctionSuccess) {
				fprintf(stderr,"Failed to initialise main document for %s: %d\n",documentFilename,(int)functionValue);
				abort(); } }

		if((functionValue=FLM_ReadDocumentInformation(
			mainDocument,
			documentFilename,
			0x00,
			false))!=FLM_FunctionSuccess)
		{
			fprintf(stderr,"Failed to read document %s information: %d\n",documentFilename,(int)functionValue);
			abort();
		}
		if((functionValue=FLM_OpenDocumentFiles(mainDocument,true))!=FLM_FunctionSuccess) {
			fprintf(stderr,"Failed to open document %s data files: %d\n",documentFilename,(int)functionValue);
			abort(); }

		if((parameterValue=getParameter("printdocument",NULL,parameterIndex))) {
			if(strcasecmp(parameterValue,"information")==0x00) {
				fprintf(stdout,"Document %s Block Size: %zu\n",documentFilename,mainDocument->blockInformation->blockSize);
				fprintf(stdout,"Document %s Data File Maximum Size: %zu\n",documentFilename,mainDocument->data->limit);
				if(mainDocument->data->filename) { fprintf(stdout,"Document %s Data File Name: %s\n",documentFilename,mainDocument->data->filename); }
				else { fprintf(stdout,"Document %s Data File Name: %s\n",documentFilename,documentFilename); }
				fprintf(stdout,"Document %s Data File Offset: %zu\n",documentFilename,mainDocument->data->offset);
				fprintf(stdout,"Document %s Current Free Block: %zu\n",documentFilename,mainDocument->blockInformation->initialFreeBlock);
				fprintf(stdout,"Document %s Index File Maximum Size: %zu\n",documentFilename,mainDocument->index->limit);
				if(mainDocument->index->filename) { fprintf(stdout,"Document %s Index File Name: %s\n",documentFilename,mainDocument->index->filename); }
				else { fprintf(stdout,"Document %s Index File Name: %s\n",documentFilename,documentFilename); }
				fprintf(stdout,"Document %s Index File Offset: %zu\n",documentFilename,mainDocument->index->offset);
				fprintf(stdout,"Document %s Maximum Blocks: %zu\n",documentFilename,mainDocument->blockInformation->blockLimit); }
			else {
				fprintf(stderr,"Invalid Print Property %s for document %s\n",parameterValue,documentFilename);
				abort(); } }

		FLM_ReleaseDocument(mainDocument,true);
		mainDocument = NULL;
		parameterIndex++;
	}
	*/

	return FLM_FUNCTION_SUCCESS;
}
