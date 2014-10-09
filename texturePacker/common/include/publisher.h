#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QString>
#include <QVector>
#include "include/settingsvo.h"

class Publisher : public QObject
{
    Q_OBJECT
public:
    explicit Publisher(const SettingsVO & svo);
    const SettingsVO & getSettingsVO() const;
    bool publish();
signals:

public slots:
    void done(bool succ, const QString & imagePath);

private:
    SettingsVO  m_svo;
    QVector<QString> m_fileLists;
    enum{MAX_THREAD_NUM = 3};
};

#endif // PUBLISHER_H
