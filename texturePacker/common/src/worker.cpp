#include "include/worker.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/fileutils.h"

Worker::Worker():
    QThread()
  , m_imageFilePath("")
  , m_inputPath("")
  , m_outputPath("")
{
}

void Worker::run()
{
    QString absInputPath = FileUtils::getAbsoluteFilePath(m_inputPath);

//    PNG png(m_imageFilePath);

//    if (!png.load())
//    {
//        //@todo load file fail
//        return false;
//    }

//    PVR * pvr = png.convertToPVR();
//    QString path = m_outputPath + "/" + m_imageFilePath.right(m_imageFilePath.length() - absInputPath.length() - 1);
//    ImageVO ivo = pvr->imagevo();
//    ivo.setFileName(path);
//    pvr->setImagevo(ivo);
//    int index = path.lastIndexOf(".");
//    path = path.left(index) + ".bip";
//    BipWriter writer(pvr);
//    FileUtils::createParentDirectory(path);
//    writer.save(path);
//    delete pvr;

    //@todo create bip ok
    done(false, "ddddddddddddddddd");
}
QString Worker::imageFilePath() const
{
    return m_imageFilePath;
}

void Worker::setImageFilePath(const QString &imageFilePath)
{
    m_imageFilePath = imageFilePath;
}
QString Worker::inputPath() const
{
    return m_inputPath;
}

void Worker::setInputPath(const QString &inputPath)
{
    m_inputPath = inputPath;
}
QString Worker::outputPath() const
{
    return m_outputPath;
}

void Worker::setOutputPath(const QString &outputPath)
{
    m_outputPath = outputPath;
}



