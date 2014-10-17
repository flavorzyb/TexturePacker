#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QString>
#include <QVector>

#include "include/worker.h"
#include "include/settingsvo.h"
#include "include/png2bipcache.h"

class Publisher : public QObject
{
    Q_OBJECT
private:
    enum{MAX_THREAD_NUM = 1};

public:
    explicit Publisher(const SettingsVO & svo);
    const SettingsVO & getSettingsVO() const;
    bool publish();
    QString fetchTask();
    QString fetchOutInfo();
    QVector<QString> succFileLists() const;
    QVector<QString> failFileLists() const;
    inline bool isFinished() const {return m_isFinished;}
    void doneFile(bool isSucc, const QString & filePath, const QString & bipFilePath, int width, int height);

private:
    void loadCacheData();
    void chopExcludePath();
    void filterMinSizeFile();

private:
    SettingsVO  m_svo;
    QVector<QString> m_fileLists;
    unsigned int m_fileCount;
    Worker m_works;
    QVector<QString> m_succFileLists;
    QVector<QString> m_failFileLists;
    QVector<QString> m_outInfoLists;
    bool m_isFinished;
    Png2BipCache m_png2BipCache;
};

#endif // PUBLISHER_H
