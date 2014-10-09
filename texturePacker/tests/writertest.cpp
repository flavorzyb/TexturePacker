#include <iostream>
#include <QFile>
#include <QDataStream>

#include "writertest.h"
#include "common/include/reader.h"
#include "common/include/fileutils.h"

WriterTest::WriterTest()
{
}

void WriterTest::init()
{
    m_writer = new Writer(4096);
}

void WriterTest::cleanup()
{
    delete m_writer;
}

void WriterTest::testWriteAll()
{
    unsigned char header[HEAD_DATA_SIZE] = {0x89, 'D', 'A', 'T', 0x0D, 0x0A, 0x1A, 0x0A};

    m_writer->copyBytes(header, HEAD_DATA_SIZE);

    QCOMPARE(m_writer->writeByte(50), true);
    QCOMPARE(m_writer->writeByte(23), true);

    QCOMPARE(m_writer->writeBoolean(true), true);
    QCOMPARE(m_writer->writeBoolean(false), true);

    QCOMPARE(m_writer->writeInt(123), true);
    QCOMPARE(m_writer->writeInt(-121), true);

    QCOMPARE(m_writer->writeFloat(0.45f), true);
    QCOMPARE(m_writer->writeFloat(-123.4f), true);

    QCOMPARE(m_writer->writeShort(111), true);
    QCOMPARE(m_writer->writeShort(-101), true);

    QCOMPARE(m_writer->writeString("hahwoadaddd."), true);
    QCOMPARE(m_writer->writeString("this is a title."), true);

    int len = m_writer->getLenght();
    unsigned char * pData = m_writer->getData();

    FileUtils::writeFile("data/writer.dat", "wb", pData, len);

    unsigned long fileSize = 0;
    pData = FileUtils::getFileData("data/writer.dat", "rb", &fileSize);
    Reader reader(pData, fileSize);
    QCOMPARE(reader.isUTF8BOM(), false);

    reader.skip(HEAD_DATA_SIZE);

    QCOMPARE(reader.readByte(), (unsigned char) 50);
    QCOMPARE(reader.readByte(), (unsigned char) 23);

    QCOMPARE(reader.readBoolean(), true);
    QCOMPARE(reader.readBoolean(), false);

    QCOMPARE(reader.readInt(), 123);
    QCOMPARE(reader.readInt(), -121);

    QCOMPARE(reader.readFloat(), 0.45f);
    QCOMPARE(reader.readFloat(), -123.4f);

    QCOMPARE(reader.readShort(), (short) 111);
    QCOMPARE(reader.readShort(), (short) -101);

    QString str = reader.readString();
    QVERIFY(str == "hahwoadaddd.");

    str = reader.readString();
    QVERIFY(str == "this is a title.");
}
