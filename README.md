CS525 Advanced Database Organization Assignment 1: Storage Manager
Group 04: Santhosh Ekambaram - A20555224 , Deepana Alluri - A20545112
Modules
Headers: dberror.h, storage_mgr.h, test_helper.h
C files: dberror.c, storage_mgr.c, test_code.c, test_assign1_1.c
Aim
We aimed to develop a basic database storage handler consisting of files organized as sets of pages. The handler should create new page files of a fixed block size (4096 bytes) and load an existing page into memory with certain metadata in the header, such as fileName, total number of pages, current page position, and mgmtInfo, acting as a direct pointer to the file's contents.
Contributions
Santhosh Ekambaram Deepana Alluri contribution: Two of us made an equal contribution to the completion of assignment 1. Through this project, we gained insights into various file operations and memory utilization techniques. Each member participated in developing test cases, storage manager functions, and documentation, ensuring an equitable distribution of effort, with each individual making a 50% contribution.
Contents
1) Instructions to run code
2) Function documentation
3) Testing
4) Memory Check
1. Instructions to Run Code
Navigate to the assignment directory in the terminal: cd assign1
Generate the final execution file: make all
Run the code: make execute
Delete the created output file and executable file: make clean
2. Function Documentation
initStorageManager
Does nothing.
createPageFile
Initialize a FILE pointer named file.
Call fopen with the given file name in write and read mode.
Return RC_WRITE_FAILED if the file pointer is invalid.
Allocate a page-sized block of memory for the new page.
Return RC_WRITE_FAILED if memory allocation fails.
Write the new page to the file.
Close the file via fclose.
Free the allocated memory.
openPageFile
Call fopen with the given name in read and write mode.
Move the file pointer to the end.
Get the file size using ftell, divide by PAGE_SIZE (4096 bytes), and update the file handler's metadata.
Set the file name and existfile.
Set page position to 0.
closePageFile
Return RC_FILE_HANDLE_NOT_INIT if the file handler or file pointer does not exist.
Call fclose on the file.
Return OK.
destroyPageFile
Open the file in read-only mode.
Return RC_FILE_NOT_FOUND if the file does not exist.
Call fclose on the file.
Call remove on the file.
readBlock
Check if the requested page number is valid.
Calculate the byte offset of the requested page.
Move the file pointer to the offset.
Load the page data into memory using fread.
Update the current page position in the file handler's metadata.
getBlockPos
Return the current page position.
Return RC_FILE_HANDLE_NOT_INIT if the file handler or page is not loaded.
readFirstBlock
Call readBlock with page number 0.
readPreviousBlock
Call readBlock with the page number decremented by one.
readCurrentBlock
Call readBlock with the current page position.
readNextBlock
Call readBlock with the page number incremented by one.
readLastBlock
Call readBlock with the total number of pages decremented by one.
writeBlock
Verify if the page number is valid.
Confirm that a file is loaded into memory.
Calculate the byte offset to the page number.
Move the file pointer by the offset.
Overwrite the page with data from memPage.
Update the file handler's metadata.
writeCurrentBlock
Check if the file is loaded.
Calculate the byte offset to the current page number.
Move the file pointer by the offset.
Overwrite the current page with data from memPage.
Increment the current page position.
appendEmptyBlock
Confirm the file is open.
Calculate the byte offset of the current page position.
Move the file pointer by the offset.
Allocate memory for a new page.
Write the new page to the file.
Update the file handler's metadata.
Set the current page position to the new page.
ensureCapacity
Confirm the file is open.
Compare the file's total number of pages to the requested pages.
Return RC_OK if the file has enough pages.
Append new pages if needed.
Update the file handler's metadata.
3. Testing
testCreateOpenClose
Testing open and close functionality.
Steps: 1. Create a new page file. 2. Open the page file. 3. Test total page count and current position. 4. Close the page file. 5. Delete the page file.
testSinglePageContent
Testing page content.
Steps: 1. Create and open a page file. 2. Read the first block to check if it is empty. 3. Write a block. 4. Read the block and verify the data. 5. Close and delete the page file.
testingBlockPositionAndCapacity
Testing block position and capacity functions.
Steps: 1. Create and open a page file. 2. Test getBlockPos function. 3. Set the total number of pages. 4. Use ensureCapacity to set and test the page count. 5. Increase and check the total page count. 6. Attempt to decrease the capacity and verify it does not work.
testingOtherPageFunctions
Testing other functions.
Steps: 1. Create and open a page file. 2. Check page count and current position. 3. Read the first block and verify it is empty. 4. Add and write data to a new block. 5. Verify data by reading the block. 6. Close and destroy the file.
4. Memory Leak
Command to check for memory leaks on Mac: leaks -atExit -- ./final
