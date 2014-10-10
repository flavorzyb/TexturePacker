#ifndef PUBLISHTHREAD_H
#define PUBLISHTHREAD_H

#include <QThread>
#include <QString>

#include "common/include/settingsvo.h"

class PublishThread : public QThread
{
    Q_OBJECT
public:
    PublishThread();

    SettingsVO getSettingsVO() const;
    void setSettingsVO(const SettingsVO & svo);

private:
    void run();

signals:
    void update(QString info);

public slots:

private:
    SettingsVO m_svo;
};

#endif // PUBLISHTHREAD_H
