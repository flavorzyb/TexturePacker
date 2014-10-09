#include "include/publisher.h"
#include "include/fileutils.h"
#include "include/png.h"
#include "include/bipwriter.h"

Publisher::Publisher(const SettingsVO & svo) :
    QObject(NULL),
    m_svo(svo)
{
}

const SettingsVO & Publisher::getSettingsVO() const
{
    return m_svo;
}

bool Publisher::publish()
{
    QVector<QString> imageFileLists = FileUtils::getAllImageFiles(m_svo.getInputPath());
    QString absInputPath = FileUtils::getAbsoluteFilePath(m_svo.getInputPath());
    QVector<QString>::const_iterator iterator = imageFileLists.constBegin();

    for (; iterator != imageFileLists.constEnd(); iterator++)
    {
        QString path = *iterator;
        PNG png(path);
        png.load();
        PVR * pvr = png.convertToPVR();
        path = m_svo.getOutputPath() + "/" + path.right(path.length() - absInputPath.length() - 1);
        ImageVO ivo = pvr->imagevo();
        ivo.setFileName(path);
        pvr->setImagevo(ivo);
        int index = path.lastIndexOf(".");
        path = path.left(index) + ".bip";
        BipWriter writer(pvr);
        FileUtils::createParentDirectory(path);
        writer.save(path);
    }

    return true;
}
