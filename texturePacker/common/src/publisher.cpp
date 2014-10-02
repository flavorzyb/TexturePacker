#include "include/publisher.h"
#include "common/include/fileutils.h"

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

    QVector<QString>::const_iterator iterator = imageFileLists.constBegin();
    for (; iterator != imageFileLists.constEnd(); iterator++)
    {
        printf("%s\n", iterator->toStdString().c_str());
    }
    return true;
}
