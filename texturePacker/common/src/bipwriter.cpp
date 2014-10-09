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

    writer->copyBytes(BIP_HEAD_DATA, HEAD_DATA_SIZE);
    // write source size
    writer->writeInt(pvr->imagevo().sourceSize().width());
    writer->writeInt(pvr->imagevo().sourceSize().height());

    // writer filename
    writer->writeString(pvr->imagevo().fileName());

    // rect
    writer->writeInt(pvr->imagevo().rect().x());
    writer->writeInt(pvr->imagevo().rect().y());
    writer->writeInt(pvr->imagevo().rect().width());
    writer->writeInt(pvr->imagevo().rect().height());

    // offset
    writer->writeInt(pvr->imagevo().offset().x());
    writer->writeInt(pvr->imagevo().offset().y());

    // source color rect
    writer->writeInt(pvr->imagevo().sourceColorRect().x());
    writer->writeInt(pvr->imagevo().sourceColorRect().y());
    writer->writeInt(pvr->imagevo().sourceColorRect().width());
    writer->writeInt(pvr->imagevo().sourceColorRect().height());

    // size
    writer->writeInt(pvr->imagevo().size().width());
    writer->writeInt(pvr->imagevo().size().height());
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
    QString tmpPath = FileUtils::createImageTempFolder() + "/" + FileUtils::getRandFileNameString() + ".pvr.ccz";
    pvr->saveCCZ(tmpPath);

    unsigned long size = 0;
    unsigned char * pData = FileUtils::getFileData(tmpPath.toStdString().c_str(), "rb", &size);
    FileUtils::unlink(tmpPath);

    if ((NULL != pData) && (size > 0))
    {
        return FileUtils::writeFile(filepath.toStdString().c_str(), "ab+", pData, size);
    }

    return false;
}
