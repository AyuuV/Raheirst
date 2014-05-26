// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Document.c

#include "Definition.h"
#include "Document.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

enum FLM_Function
FLM_NewDocument(
	struct FLM_Document** _document)
{
	struct FLM_Document* targetDocument = NULL;
	if(!_document||*_document) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!(targetDocument=(struct FLM_Document*)malloc(sizeof(*targetDocument)))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }

	targetDocument->blockInformation = (struct FLM_DocumentBlockInformation*)malloc(sizeof(*(targetDocument->blockInformation)));
	targetDocument->data = (struct FLM_DocumentDataFile*)malloc(sizeof(*(targetDocument->data)));
	targetDocument->index = (struct FLM_DocumentDataFile*)malloc(sizeof(*(targetDocument->index)));

	if(targetDocument->blockInformation&&targetDocument->data&&targetDocument->index) {
		targetDocument->blockInformation->blockLimit = FLM_DOCUMENT_DEFAULT_BLOCKLIMIT;
		targetDocument->blockInformation->blockSize = FLM_DOCUMENT_DEFAULT_BLOCKSIZE;
		targetDocument->blockInformation->initialFreeBlock = 0x00;
		targetDocument->data->file = NULL;
		targetDocument->data->filename = NULL;
		targetDocument->data->limit = FLM_DOCUMENT_DEFAULT_DATAFILELIMIT;
		targetDocument->data->offset = FLM_DOCUMENT_DEFAULT_DATAFILEOFFSET;
		targetDocument->index->file = NULL;
		targetDocument->index->filename = NULL;
		targetDocument->index->limit = FLM_DOCUMENT_DEFAULT_DATAFILELIMIT;
		targetDocument->index->offset = FLM_DOCUMENT_DEFAULT_DATAFILEOFFSET;
		return FLM_FunctionSuccess; }

	if(targetDocument->blockInformation) { free(targetDocument->blockInformation); }
	if(targetDocument->data) { free(targetDocument->data); }
	if(targetDocument->index) { free(targetDocument->index); }

	free(targetDocument);

	return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure;
}

enum FLM_Function
FLM_OpenDocument(
	struct FLM_Document** _document,
	const char* _documentFilename,
	const size_t _documentFileOffset)
{
	FILE* documentFile = NULL;

	if(!(_document&&_documentFilename)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!(documentFile=fopen(_documentFilename,"rb"))) { return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileAccessFailure; }
	if(!*_document||!(*_document=(struct FLM_Document*)malloc(sizeof(**_document)))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }

	(void)_documentFileOffset;

	if(fclose(documentFile)!=0x00) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_WriteDocumentInformation(
	const struct FLM_Document* _document,
	const char* _documentFilename,
	const size_t _documentFileOffset)
{
	FILE* documentFile = NULL;

	size_t documentDataOffset = _documentFileOffset;
	size_t documentIndexOffset = _documentFileOffset;

	if(!(_document&&_documentFilename)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!_document->blockInformation||!_document->data||!_document->index) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!_document->data->filename||!_document->index->filename) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	documentDataOffset += sizeof(_document->blockInformation->blockLimit);
	documentDataOffset += sizeof(_document->blockInformation->blockSize);
	documentDataOffset += sizeof(_document->blockInformation->initialFreeBlock);

	documentIndexOffset += documentDataOffset;
	documentIndexOffset += strlen(_document->data->filename)+0x01;
	documentIndexOffset += sizeof(_document->data->limit);
	documentIndexOffset += sizeof(_document->data->offset);

	if(!(documentFile=fopen(_documentFilename,"r+b"))) { if(!(documentFile=fopen(_documentFilename,"wb"))) { return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileAccessFailure; } }

	if(FLM_WriteDocumentBlockInformation(
		documentFile,
		_document->blockInformation,
		_documentFileOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionSubFunctionFailure; }

	if(FLM_WriteDocumentDataFileInformation(
		documentFile,
		_document->data,
		documentDataOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionSubFunctionFailure; }

	if(FLM_WriteDocumentDataFileInformation(
		documentFile,
		_document->index,
		documentIndexOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionSubFunctionFailure; }

	if(fclose(documentFile)!=0x00) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_WriteDocumentBlockInformation(
	FILE* _documentFile,
	const struct FLM_DocumentBlockInformation* _documentBlockInformation,
	const size_t _documentOffset)
{
	if(!(_documentBlockInformation&&_documentFile)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	size_t currentOffset = _documentOffset;
	size_t documentBlockLimitSize = sizeof(_documentBlockInformation->blockLimit);
	size_t documentBlockSizeSize = sizeof(_documentBlockInformation->blockSize);
	size_t documentInitialFreeBlockSize = sizeof(_documentBlockInformation->initialFreeBlock);


	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentBlockInformation->blockLimit),
		documentBlockLimitSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += documentBlockLimitSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentBlockInformation->blockSize),
		documentBlockSizeSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += documentBlockSizeSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentBlockInformation->initialFreeBlock),
		documentInitialFreeBlockSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_WriteDocumentDataFileInformation(
	FILE* _documentFile,
	const struct FLM_DocumentDataFile* _documentDataFileInformation,
	const size_t _documentOffset)
{
	if(!(_documentDataFileInformation&&_documentDataFileInformation->filename&&_documentFile)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	size_t currentOffset = _documentOffset;
	size_t documentDataFileNameLength = strlen(_documentDataFileInformation->filename)+0x01;
	size_t documentDataFileLimitSize = sizeof(_documentDataFileInformation->limit);
	size_t documentDataFileOffsetSize = sizeof(_documentDataFileInformation->offset);

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentDataFileInformation->filename),
		sizeof(*(_documentDataFileInformation->filename)),
		documentDataFileNameLength,
		_documentFile)!=documentDataFileNameLength)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += documentDataFileNameLength; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentDataFileInformation->limit),
		documentDataFileLimitSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += documentDataFileLimitSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&(_documentDataFileInformation->offset),
		documentDataFileOffsetSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { return FLM_FunctionSuccess; }
}
