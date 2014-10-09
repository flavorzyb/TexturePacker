#include "include/bipreader.h"

BipReader::BipReader(const QString &fileName):
    BipAbstract()
  , m_fileName(fileName)
{
}

BipReader::~BipReader()
{
}

PVR * BipReader::load()
{
    return NULL;
}

PVR *BipReader::load(const QString &fileName)
{
    setFileName(fileName);
    return load();
}

QString BipReader::fileName() const
{
    return m_fileName;
}

void BipReader::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

