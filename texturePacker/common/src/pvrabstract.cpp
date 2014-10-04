#include "include/pvrabstract.h"

PVRAbstract::PVRAbstract():
    m_filePath("")
  , m_width(0)
  , m_height(0)
{
}

PVRAbstract::PVRAbstract(QString filename):
    m_filePath(filename)
  , m_width(0)
  , m_height(0)
{
}

bool PVRAbstract::load(QString filename)
{
    setFilePath(filename);

    return load();
}

int PVRAbstract::width() const
{
    return m_width;
}

void PVRAbstract::setWidth(int width)
{
    m_width = width;
}
int PVRAbstract::height() const
{
    return m_height;
}

void PVRAbstract::setHeight(int height)
{
    m_height = height;
}

const QString & PVRAbstract::filePath() const
{
    return m_filePath;
}

void PVRAbstract::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}



