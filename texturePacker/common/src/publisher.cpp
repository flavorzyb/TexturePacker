#include "include/publisher.h"
#include "include/fileutils.h"
#include "include/png.h"
#include "include/bipwriter.h"
#include "include/worker.h"

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
    m_fileLists = FileUtils::getAllImageFiles(m_svo.getInputPath());
    QString absInputPath = FileUtils::getAbsoluteFilePath(m_svo.getInputPath());

    Worker workers[MAX_THREAD_NUM];
    for (int i = 0; i < MAX_THREAD_NUM; ++i)
    {
        connect(&workers[i], SIGNAL(done(bool, const QString &)), this, SLOT(done(bool, const QString &)));
        workers[i].setImageFilePath("aaaaaa");
        workers[i].run();
    }

//    for (int i = 0; i < MAX_THREAD_NUM; ++i)
//    {
//        workers[i].wait();
//    }

    return true;
}

void Publisher::done(bool succ, const QString &imagePath)
{
    char str[1024] = {0};
    sprintf(str, "succ:%s path:%s\n", succ ? "ok" : "fail", imagePath.toStdString().c_str());

    FileUtils::writeFile("/Users/admin/tmp/a.txt", "ab+", str, strlen(str) * sizeof(char));
}
