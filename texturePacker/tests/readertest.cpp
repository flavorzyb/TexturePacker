#include "readertest.h"
#include "common/include/fileutils.h"

ReaderTest::ReaderTest()
{
}

void ReaderTest::init()
{
    unsigned long fileSize = 0;
    unsigned char * pData = FileUtils::getFileData("data/reader.dat", "rb", &fileSize);
    m_reader = new Reader(pData, fileSize);
}

void ReaderTest::cleanup()
{
    delete m_reader;
}

void ReaderTest::testReadAll()
{
    QCOMPARE(m_reader->isUTF8BOM(), true);
    m_reader->skipUTF8BOM();

    m_reader->skip(HEAD_DATA_SIZE);

    QCOMPARE(m_reader->readByte(), (unsigned char) 10);
    QCOMPARE(m_reader->readByte(), (unsigned char) 3);

    QCOMPARE(m_reader->readBoolean(), false);
    QCOMPARE(m_reader->readBoolean(), true);

    QCOMPARE(m_reader->readInt(), 200);
    QCOMPARE(m_reader->readInt(), 6698);

    QCOMPARE(m_reader->readFloat(), 1.98f);
    QCOMPARE(m_reader->readFloat(), -298.4f);

    QCOMPARE(m_reader->readShort(), (short) 123);
    QCOMPARE(m_reader->readShort(), (short) -12);

    QString str = m_reader->readString();
    QVERIFY(str == "this is a test string.");

    str = m_reader->readString();
    QVERIFY(str == "hahahaha.");
}
