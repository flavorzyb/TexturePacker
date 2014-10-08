#include "readertest.h"
#include "common/include/fileutils.h"

ReaderTest::ReaderTest()
{
}

void ReaderTest::init()
{
    unsigned long fileSize = 0;
    unsigned char * pData = FileUtils::getFileData("", "rb", &fileSize);
    m_reader = new Reader(pData, fileSize);
}

void ReaderTest::cleanup()
{
    delete m_reader;
}

void ReaderTest::testReadAll()
{
}
