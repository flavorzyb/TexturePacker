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
    const QVector<FrameVO> & frameLists = ivo.frames();
    unsigned int frameCount = frameLists.size();

    writer->copyBytes(BIP_HEAD_DATA, HEAD_DATA_SIZE);

    writer->writeInt(frameCount);

    for(unsigned int i = 0; i < frameCount; i++)
    {
        const FrameVO & frame = frameLists.at(i);

        // writer filename
        writer->writeString(frame.name());

        // md5string
        writer->writeString(frame.md5String());

        // rect
        writer->writeInt(frame.rect().x());
        writer->writeInt(frame.rect().y());
        writer->writeInt(frame.rect().width());
        writer->writeInt(frame.rect().height());

        // offset
        writer->writeInt(frame.offset().x());
        writer->writeInt(frame.offset().y());

        // rotated
        writer->writeBoolean(frame.rotated());

        // source color rect
        writer->writeInt(frame.sourceColorRect().x());
        writer->writeInt(frame.sourceColorRect().y());
        writer->writeInt(frame.sourceColorRect().width());
        writer->writeInt(frame.sourceColorRect().height());

        // write source size
        writer->writeInt(frame.sourceSize().width());
        writer->writeInt(frame.sourceSize().height());
    }

    // size
    writer->writeInt(ivo.size().width());
    writer->writeInt(ivo.size().height());

    // writer filename
    writer->writeString(ivo.fileName());
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
