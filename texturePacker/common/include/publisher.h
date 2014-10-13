#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMutex>

#include "include/worker.h"
#include "include/settingsvo.h"
#include "include/png2bipcache.h"

class Publisher : public QObject
{
    Q_OBJECT
private:
    enum{MAX_THREAD_NUM = 4};

public:
    explicit Publisher(const SettingsVO & svo);
    const SettingsVO & getSettingsVO() const;
    bool publish();
    QString fetchTask();
    QString fetchOutInfo();
    QVector<QString> succFileLists() const;
    QVector<QString> failFileLists() const;
    inline bool isFinished() const {return m_isFinished;}
    void doneFile(bool isSucc, const QString & filePath, const QString & bipFilePath);

private:
    void loadCacheData();

private:
    SettingsVO  m_svo;
    QVector<QString> m_fileLists;
    unsigned int m_fileCount;
    QMutex m_mutex;
    Worker m_works[MAX_THREAD_NUM];
    QVector<QString> m_succFileLists;
    QVector<QString> m_failFileLists;
    QVector<QString> m_outInfoLists;
    QMutex m_doneMutex;
    bool m_isFinished;
    Png2BipCache m_png2BipCache;
};

#endif // PUBLISHER_H
