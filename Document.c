// Rainbow Heart ~ Iris Star
// Flowering Love Maiden
// Document.c

#include "Definition.h"

#include "Document.h"

#include <stdbool.h>
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
		targetDocument->blockInformation->indexEntrySize = FLM_DOCUMENT_DEFAULT_ENTRYSIZE;
		targetDocument->blockInformation->initialFreeBlock = 0x00;
		targetDocument->data->file = NULL;
		targetDocument->data->filename = NULL;
		targetDocument->data->limit = FLM_DOCUMENT_DEFAULT_DATAFILELIMIT;
		targetDocument->data->offset = FLM_DOCUMENT_DEFAULT_DATAFILEOFFSET;
		targetDocument->index->file = NULL;
		targetDocument->index->filename = NULL;
		targetDocument->index->limit = FLM_DOCUMENT_DEFAULT_DATAFILELIMIT;
		targetDocument->index->offset = FLM_DOCUMENT_DEFAULT_DATAFILEOFFSET;

		*_document = targetDocument;

		return FLM_FunctionSuccess; }

	if(targetDocument->blockInformation) { free(targetDocument->blockInformation); }
	if(targetDocument->data) { free(targetDocument->data); }
	if(targetDocument->index) { free(targetDocument->index); }

	free(targetDocument);

	return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure;
}

enum FLM_Function
FLM_OpenDocumentFiles(
	struct FLM_Document* _document,
	const bool _releasePrevious)
{
	if(!_document||
		!_document->blockInformation||
		!_document->data||
		!_document->index) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	if(_document->data->filename) {
		FILE* documentDataFile = fopen(_document->data->filename,"r+b");
		if(!documentDataFile&&!(documentDataFile=fopen(_document->data->filename,"w+b"))) { return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileAccessFailure; }
		if(_releasePrevious&&_document->data->file&&fclose(_document->data->file)!=0x00) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
		_document->data->file = documentDataFile; }
	if(_document->index->filename) {
		FILE* documentIndexFile = fopen(_document->index->filename,"r+b");
		if(!documentIndexFile&&!(documentIndexFile=fopen(_document->index->filename,"w+b"))) { return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileAccessFailure; }
		if(_releasePrevious&&_document->index->file&&fclose(_document->index->file)!=0x00) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
		_document->index->file = documentIndexFile; }

	return FLM_FunctionSuccess;
}

enum FLM_Function
FLM_ReadDocumentInformation(
	struct FLM_Document* _document,
	const char* _documentFilename,
	const size_t _documentFileOffset,
	const bool _ignoreExternal)
{
	FILE* documentFile = NULL;

	size_t documentDataFilenameLength = 0x00;
	size_t documentDataOffset = _documentFileOffset;
	size_t documentIndexOffset = 0x00;

	bool usingMasterFile = false;

	if(!(_document&&_documentFilename)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!_document->blockInformation||!_document->data||!_document->index) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	if(!_ignoreExternal) {
		if(_document->data) {
			if(_document->data->file&&fclose(_document->data->file)) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
			if(_document->data->filename) { free(_document->data->filename); } }
		if(_document->index) {
			if(_document->index->file&&fclose(_document->index->file)) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
			if(_document->index->filename) { free(_document->index->filename); } } }

	if(_document->data) {
		_document->data->file = NULL;
		_document->data->filename = NULL; }
	if(_document->index) {
		_document->index->file = NULL;
		_document->index->filename = NULL; }

	documentDataOffset += sizeof(_document->blockInformation->blockLimit);
	documentDataOffset += sizeof(_document->blockInformation->blockSize);
	documentDataOffset += sizeof(_document->blockInformation->initialFreeBlock);

	documentIndexOffset += documentDataOffset;
	documentIndexOffset += sizeof(documentDataFilenameLength);
	documentIndexOffset += sizeof(_document->data->limit);
	documentIndexOffset += sizeof(_document->data->offset);

	if(!(documentFile=fopen(_documentFilename,"rb"))) { return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileAccessFailure; }

	if(FLM_ReadDocumentBlockInformation(
		documentFile,
		_document->blockInformation,
		_documentFileOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionSubFunctionFailure; }

	if(FLM_ReadDocumentDataFileInformation(
		documentFile,
		_document->data,
		&documentDataFilenameLength,
		&usingMasterFile,
		documentDataOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionSubFunctionFailure; }
	else { documentIndexOffset += documentDataFilenameLength; }

	if(FLM_ReadDocumentDataFileInformation(
		documentFile,
		_document->index,
		NULL,
		&usingMasterFile,
		documentIndexOffset)!=FLM_FunctionSuccess)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionSubFunctionFailure; }

	if(!usingMasterFile&&fclose(documentFile)!=0x00) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_ReadDocumentBlockInformation(
	FILE* _documentFile,
	struct FLM_DocumentBlockInformation* _documentBlockInformation,
	const size_t _documentOffset)
{
	if(!(_documentBlockInformation&&_documentFile)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	size_t currentOffset = _documentOffset;
	size_t documentBlockLimitSize = sizeof(_documentBlockInformation->blockLimit);
	size_t documentBlockSizeSize = sizeof(_documentBlockInformation->blockSize);
	size_t documentIndexEntrySize = sizeof(_documentBlockInformation->indexEntrySize);
	size_t documentInitialFreeBlockSize = sizeof(_documentBlockInformation->initialFreeBlock);


	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentBlockInformation->blockLimit),
		documentBlockLimitSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { currentOffset += documentBlockLimitSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentBlockInformation->blockSize),
		documentBlockSizeSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { currentOffset += documentBlockSizeSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentBlockInformation->indexEntrySize),
		documentIndexEntrySize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { currentOffset += documentIndexEntrySize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentBlockInformation->initialFreeBlock),
		documentInitialFreeBlockSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_ReadDocumentDataFileInformation(
	FILE* _documentFile,
	struct FLM_DocumentDataFile* _documentDataFileInformation,
	size_t* _documentDataFileNameLength,
	bool* _documentDataFile,
	const size_t _documentOffset)
{
	if(!(_documentDataFileInformation&&_documentFile)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	char* documentDataFileName = NULL;

	size_t currentOffset = _documentOffset;
	size_t documentDataFileNameLength = 0x00;
	size_t documentDataFileLimitSize = sizeof(_documentDataFileInformation->limit);
	size_t documentDataFileOffsetSize = sizeof(_documentDataFileInformation->offset);

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&documentDataFileNameLength,
		sizeof(documentDataFileNameLength),
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { currentOffset += sizeof(documentDataFileNameLength); }

	if(!(documentDataFileName=(char*)malloc(documentDataFileNameLength+0x01))) { return FLM_FunctionFailure|FLM_FunctionMemoryAllocationFailure; }
	else if(_documentDataFileInformation->filename) { free(_documentDataFileInformation->filename); }
	_documentDataFileInformation->filename = documentDataFileName;
	_documentDataFileInformation->filename[documentDataFileNameLength] = '\0';

	if(_documentDataFileNameLength) { *_documentDataFileNameLength = documentDataFileNameLength; }

	if(documentDataFileNameLength) {
		if(fseek(
			_documentFile,
			currentOffset,
			SEEK_SET)!=0x00)
		{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
		if(fread(
			_documentDataFileInformation->filename,
			sizeof(*(_documentDataFileInformation->filename)),
			documentDataFileNameLength,
			_documentFile)!=documentDataFileNameLength)
		{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
		else { currentOffset += documentDataFileNameLength; }
		if(_documentDataFile) { *_documentDataFile = false; }
		_documentDataFileInformation->file = NULL; }
	else {
		if(_documentDataFile) { *_documentDataFile = true; }
		_documentDataFileInformation->file = _documentFile;
		_documentDataFileInformation->filename = NULL; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentDataFileInformation->limit),
		documentDataFileLimitSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { currentOffset += documentDataFileLimitSize; }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fread(
		&(_documentDataFileInformation->offset),
		documentDataFileOffsetSize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionInputAccessFailure|FLM_FunctionFileReadFailure; }
	else { return FLM_FunctionSuccess; }
}

enum FLM_Function
FLM_ReleaseDocument(
	struct FLM_Document* _document,
	const bool _releaseExternal)
{
	bool ignoreIndexFile = false;
	bool ignoreIndexFileName = false;

	if(_document) {
		if(_document->blockInformation) { free(_document->blockInformation); }
		if(_document->data) {
			if(_document->index) {
				if(_document->index->file==_document->data->file) { ignoreIndexFile = true; }
				if(_document->index->filename==_document->data->filename) { ignoreIndexFileName = true; } }
			if(_document->data->file&&_releaseExternal&&fclose(_document->data->file)) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
			if(_document->data->filename&&_releaseExternal) { free(_document->data->filename); }
			free(_document->data); }
		if(_document->index) {
			if(!ignoreIndexFile&&_document->index->file&&_releaseExternal&&fclose(_document->index->file)) { return FLM_FunctionFailure|FLM_FunctionFileClosureFailure; }
			if(!ignoreIndexFileName&&_document->index->filename&&_releaseExternal) { free(_document->index->filename); }
			free(_document->index); }
		free(_document); }

	return FLM_FunctionSuccess;
}

enum FLM_Function
FLM_WriteDocumentInformation(
	const struct FLM_Document* _document,
	const char* _documentFilename,
	const size_t _documentFileOffset)
{
	FILE* documentFile = NULL;

	size_t documentDataOffset = _documentFileOffset;
	size_t documentIndexOffset = 0x00;

	size_t documentDataFilenameLength = 0x00;

	if(!(_document&&_documentFilename)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!_document->blockInformation||!_document->data||!_document->index) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }
	if(!_document->data->filename||!_document->index->filename) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	documentDataFilenameLength = strlen(_document->data->filename);

	documentDataOffset += sizeof(_document->blockInformation->blockLimit);
	documentDataOffset += sizeof(_document->blockInformation->blockSize);
	documentDataOffset += sizeof(_document->blockInformation->initialFreeBlock);

	documentIndexOffset += documentDataOffset;
	documentIndexOffset += sizeof(documentDataFilenameLength);
	documentIndexOffset += documentDataFilenameLength;
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
	size_t documentIndexEntrySize = sizeof(_documentBlockInformation->indexEntrySize);
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
		&(_documentBlockInformation->indexEntrySize),
		documentIndexEntrySize,
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += documentIndexEntrySize; }

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
	if(!(_documentDataFileInformation&&_documentFile)) { return FLM_FunctionError|FLM_FunctionInvalidParameters; }

	size_t currentOffset = _documentOffset;
	size_t documentDataFileNameLength = 0x00;
	size_t documentDataFileLimitSize = sizeof(_documentDataFileInformation->limit);
	size_t documentDataFileOffsetSize = sizeof(_documentDataFileInformation->offset);

	if(_documentDataFileInformation->filename) { documentDataFileNameLength = strlen(_documentDataFileInformation->filename); }

	if(fseek(
		_documentFile,
		currentOffset,
		SEEK_SET)!=0x00)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
	if(fwrite(
		&documentDataFileNameLength,
		sizeof(documentDataFileNameLength),
		0x01,
		_documentFile)!=0x01)
	{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
	else { currentOffset += sizeof(documentDataFileNameLength); }

	if(documentDataFileNameLength) {
		if(fseek(
			_documentFile,
			currentOffset,
			SEEK_SET)!=0x00)
		{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileSeekFailure; }
		if(fwrite(
			_documentDataFileInformation->filename,
			sizeof(*(_documentDataFileInformation->filename)),
			documentDataFileNameLength,
			_documentFile)!=documentDataFileNameLength)
		{ return FLM_FunctionFailure|FLM_FunctionOutputAccessFailure|FLM_FunctionFileWriteFailure; }
		else { currentOffset += documentDataFileNameLength; } }

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
