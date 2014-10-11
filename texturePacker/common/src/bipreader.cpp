#include "include/bipreader.h"
#include "include/fileutils.h"
#include "include/reader.h"

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
    unsigned long fileSize = 0;
    unsigned char *pData = FileUtils::getFileData(m_fileName.toStdString().c_str(), "rb", &fileSize);

    if ((pData == NULL) || (fileSize == 0))
    {
        return NULL;
    }

    Reader reader(pData, fileSize);

    if (reader.isUTF8BOM())
    {
        reader.skipUTF8BOM();
    }

    if (!isBipFile(reader.getData(), reader.getSize()))
    {
        return NULL;
    }

    reader.skip(HEAD_DATA_SIZE);
    reader.readInt();
    ImageVO ivo(reader.readInt(), reader.readInt());
    ivo.setFileName(reader.readString());
    ivo.setMd5String(reader.readString());
    ivo.setRect(reader.readInt(), reader.readInt(), reader.readInt(), reader.readInt());
    ivo.setRotated(reader.readBoolean());
    ivo.setOffset(reader.readInt(), reader.readInt());
    ivo.setSourceColorRect(reader.readInt(), reader.readInt(), reader.readInt(), reader.readInt());
    ivo.setSize(reader.readInt(), reader.readInt());

    PVR * result = new PVR;

    if (result->loadCCZData(reader.getData(), reader.getSize()))
    {
        result->setImagevo(ivo);
        return result;
    }

    delete result;

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

