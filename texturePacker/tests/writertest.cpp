#include <iostream>
#include <QFile>
#include <QDataStream>

#include "writertest.h"

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
    unsigned char header[] = {0x89, 'D', 'A', 'T', 0x0D, 0x0A, 0x1A, 0x0A};

    for (int i = 0; i < HEAD_DATA_SIZE; ++i)
    {
        m_writer->writeByte(header[i]);
    }

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

    unsigned char * pData = m_writer->getData();
    int len = m_writer->getLenght();

    QFile file("data/writer.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.writeBytes((char *)pData, len);
    file.close();
}
