#include "include/worker.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/fileutils.h"
#include "include/publisher.h"

Worker::Worker():
    QThread()
  , m_imageFilePath("")
  , m_inputPath("")
  , m_outputPath("")
  ,m_publisher(NULL)
{
}

void Worker::run()
{
    if (m_publisher==NULL)
    {
        return ;
    }


    for (;;)
    {
        m_imageFilePath = m_publisher->fetchTask();
        if (m_imageFilePath.length() == 0)
        {
            break;
        }

        PNG png(m_imageFilePath);
        if (!png.load())
        {
            m_publisher->doneFile(false, m_imageFilePath);
            return ;
        }

        PVR * pvr = png.convertToPVR();
        QString path = m_outputPath + "/" + m_imageFilePath.right(m_imageFilePath.length() - m_inputPath.length() - 1);
        ImageVO ivo = pvr->imagevo();
        ivo.setFileName(path);
        pvr->setImagevo(ivo);
        int index = path.lastIndexOf(".");
        path = path.left(index) + ".bip";
        BipWriter writer(pvr);
        FileUtils::createParentDirectory(path);
        writer.save(path);
        m_publisher->doneFile(true, m_imageFilePath);
    }
}

void Worker::setPublisher(Publisher *publisher)
{
    m_publisher = publisher;
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



