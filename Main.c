// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Main.c

#include "Definition.h"
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
	char* defaultValue)
{
	char* delimiterPosition = NULL;
	char* parameterValue = NULL;
	int index = 0x00;

	for(index=0x00;
		index<__argumentCount;
		index++)
	{
		if(!(delimiterPosition=strchr(__argumentArray[index],'='))) { continue; }
		if(strlen(parameterName)!=(size_t)(delimiterPosition-__argumentArray[index])) { continue; }
		if(strncasecmp(__argumentArray[index],parameterName,delimiterPosition-__argumentArray[index])==0x00) {
			parameterValue = delimiterPosition+0x01;
			break; }
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

	char* documentFilename = NULL;
	char* parameterValue = NULL;

	struct FLM_Document* mainDocument = NULL;

	if((parameterValue=getParameter("version",NULL))) {
		if(strcasecmp(parameterValue,"display")==0x00) { fprintf(stdout,"[ **** Rainbow Heart ~ Iris Star **** ]\n --= Flowering Love Maiden =-- \nVersion 0.0.1\n"); }
		else if(strcasecmp(parameterValue,"string")==0x00) { fprintf(stdout,"version 0.0.1\n"); }
		else if(strcasecmp(parameterValue,"value")==0x00) { fprintf(stdout,"0.0.1\n"); }
		else {
			fprintf(stderr,"Invalid Version Display Mode [%s]\n",parameterValue);
			return FLM_FUNCTION_ERROR; } }

	if((documentFilename=getParameter("format",NULL))) {
		if(FLM_NewDocument(&mainDocument)!=FLM_FunctionSuccess) { return FLM_FUNCTION_FAILURE; }
		if((parameterValue=getParameter("blocklimit",NULL))) { mainDocument->blockInformation->blockLimit = strtoul(parameterValue,NULL,0x00); }
		if((parameterValue=getParameter("blocksize",NULL))) { mainDocument->blockInformation->blockSize = strtoul(parameterValue,NULL,0x00); }
		if((parameterValue=getParameter("datalimit",NULL))) { mainDocument->data->limit = strtoul(parameterValue,NULL,0x00); }
		if((parameterValue=getParameter("dataoffset",NULL))) { mainDocument->data->offset = strtoul(parameterValue,NULL,0x00); }
		if((parameterValue=getParameter("indexlimit",NULL))) { mainDocument->index->limit = strtoul(parameterValue,NULL,0x00); }
		if((parameterValue=getParameter("indexoffset",NULL))) { mainDocument->index->offset = strtoul(parameterValue,NULL,0x00); }

		mainDocument->data->filename = getParameter("datafile","data.datafile");
		mainDocument->index->filename = getParameter("indexfile","index.datafile");

		if(FLM_WriteDocumentInformation(mainDocument,documentFilename,0x00)!=FLM_FunctionSuccess) { return FLM_FUNCTION_FAILURE; }

		FLM_ReleaseDocument(mainDocument,false);
		mainDocument = NULL; }

	FLM_ReleaseDocument(mainDocument,true);

	return FLM_FUNCTION_SUCCESS;
}
