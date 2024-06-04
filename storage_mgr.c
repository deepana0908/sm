#include "storage_mgr.h"
#include "dberror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initStorageManager(void) {
    
}

RC createPageFile(char *fileName) {
    FILE *file = fopen(fileName, "w+");
    if (file == NULL) return RC_WRITE_FAILED;

    char *emptyPage = (char *)calloc(PAGE_SIZE, sizeof(char));
    fwrite(emptyPage, sizeof(char), PAGE_SIZE, file);
    free(emptyPage);

    fclose(file);
    return RC_OK;
}

RC openPageFile(char *fileName, SM_FileHandle *fHandle) {
    FILE *file = fopen(fileName, "r+");
    if (file == NULL) return RC_FILE_NOT_FOUND;

    fHandle->fileName = fileName;
    fHandle->filePointer = file;
    
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fHandle->totalNumPages = fileSize / PAGE_SIZE;
    fHandle->curPagePos = 0;

    return RC_OK;
}

RC closePageFile(SM_FileHandle *fHandle) {
    if (fHandle->filePointer == NULL) return RC_FILE_HANDLE_NOT_INIT;

    fclose(fHandle->filePointer);
    fHandle->filePointer = NULL;
    return RC_OK;
}

RC destroyPageFile(char *fileName) {
    if (remove(fileName) != 0) return RC_FILE_NOT_FOUND;
    return RC_OK;
}

RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum >= fHandle->totalNumPages || pageNum < 0) return RC_READ_NON_EXISTING_PAGE;

    fseek(fHandle->filePointer, pageNum * PAGE_SIZE, SEEK_SET);
    fread(memPage, sizeof(char), PAGE_SIZE, fHandle->filePointer);
    fHandle->curPagePos = pageNum;

    return RC_OK;
}

RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum >= fHandle->totalNumPages || pageNum < 0) return RC_WRITE_FAILED;

    fseek(fHandle->filePointer, pageNum * PAGE_SIZE, SEEK_SET);
    fwrite(memPage, sizeof(char), PAGE_SIZE, fHandle->filePointer);
    fHandle->curPagePos = pageNum;

    return RC_OK;
}

RC appendEmptyBlock(SM_FileHandle *fHandle) {
    char *emptyPage = (char *)calloc(PAGE_SIZE, sizeof(char));
    fseek(fHandle->filePointer, 0, SEEK_END);
    fwrite(emptyPage, sizeof(char), PAGE_SIZE, fHandle->filePointer);
    free(emptyPage);

    fHandle->totalNumPages++;
    return RC_OK;
}

RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle) {
    if (fHandle->totalNumPages < numberOfPages) {
        while (fHandle->totalNumPages < numberOfPages) {
            appendEmptyBlock(fHandle);
        }
    }
    return RC_OK;
}
