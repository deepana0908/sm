#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

char *testName;

void testCreateOpenCloseDestroy();
void testReadWriteBlocks();

int main(void) {
    testName = "";

    testCreateOpenCloseDestroy();
    testReadWriteBlocks();

    return 0;
}

void testCreateOpenCloseDestroy() {
    SM_FileHandle fh;
    testName = "testCreateOpenCloseDestroy";

    TEST_CHECK(createPageFile("testfile.bin"));
    TEST_CHECK(openPageFile("testfile.bin", &fh));
    ASSERT_EQUALS_STRING("testfile.bin", fh.fileName, "filename correct");
    ASSERT_EQUALS_INT(1, fh.totalNumPages, "expecting 1 page in new file");

    TEST_CHECK(closePageFile(&fh));
    TEST_CHECK(destroyPageFile("testfile.bin"));

    TEST_DONE();
}

void testReadWriteBlocks() {
    SM_FileHandle fh;
    SM_PageHandle ph = (SM_PageHandle) malloc(PAGE_SIZE);
    testName = "testReadWriteBlocks";

    TEST_CHECK(createPageFile("testfile.bin"));
    TEST_CHECK(openPageFile("testfile.bin", &fh));

    // Write to first block
    strcpy(ph, "This is a test.");
    TEST_CHECK(writeBlock(0, &fh, ph));

    // Read from first block
    memset(ph, 0, PAGE_SIZE);
    TEST_CHECK(readBlock(0, &fh, ph));
    ASSERT_EQUALS_STRING("This is a test.", ph, "first block content");

    // Clean up
    TEST_CHECK(closePageFile(&fh));
    TEST_CHECK(destroyPageFile("testfile.bin"));
    free(ph);

    TEST_DONE();
}
