#include "include/bipwriter.h"
#include "include/writer.h"
#include "include/fileutils.h"

BipWriter::BipWriter(PVR *pvr):BipAbstract()
{
    setPvr(pvr);
}

BipWriter::~BipWriter()
{
}

bool BipWriter::save(const QString &filepath)
{
    PVR * pvr = this->pvr();
    if (NULL == pvr)
    {
        return false;
    }

    if (pvr->isEmpty())
    {
        return false;
    }

    Writer writer;
    initWriter(&writer);

    if (writerHeadData(&writer, filepath) && writerPVRData(filepath))
    {
        return true;
    }

    return false;
}

void BipWriter::initWriter(Writer * writer)
{
    PVR * pvr = this->pvr();
    ImageVO ivo = pvr->imagevo();

    writer->copyBytes(BIP_HEAD_DATA, HEAD_DATA_SIZE);
    writer->writeInt(1);
    // write source size
    writer->writeInt(ivo.sourceSize().width());
    writer->writeInt(ivo.sourceSize().height());

    // writer filename
    writer->writeString(ivo.fileName());

    // md5string
    writer->writeString(ivo.md5String());

    // rect
    writer->writeInt(ivo.rect().x());
    writer->writeInt(ivo.rect().y());
    writer->writeInt(ivo.rect().width());
    writer->writeInt(ivo.rect().height());

    // rotated
    writer->writeBoolean(ivo.rotated());

    // offset
    writer->writeInt(ivo.offset().x());
    writer->writeInt(ivo.offset().y());

    // source color rect
    writer->writeInt(ivo.sourceColorRect().x());
    writer->writeInt(ivo.sourceColorRect().y());
    writer->writeInt(ivo.sourceColorRect().width());
    writer->writeInt(ivo.sourceColorRect().height());

    // size
    writer->writeInt(ivo.size().width());
    writer->writeInt(ivo.size().height());
}

bool BipWriter::writerHeadData(Writer *writer, const QString & filepath)
{
    if (NULL == writer)
    {
        return false;
    }
    unsigned char * pData = writer->getData();
    unsigned int len = writer->getLenght();

    if (len < 1)
    {
        return false;
    }

    return FileUtils::writeFile(filepath.toStdString().c_str(), "wb", pData, len);
}

bool BipWriter::writerPVRData(const QString &filepath)
{
    PVR * pvr = this->pvr();
    unsigned long size = 0;
    unsigned char *pData = pvr->saveCCZToBuffer(&size);

    if ((NULL != pData) && (size > 0))
    {
        bool result = FileUtils::writeFile(filepath.toStdString().c_str(), "ab+", pData, size);
        delete [] pData;
        return result;
    }

    return false;
}
