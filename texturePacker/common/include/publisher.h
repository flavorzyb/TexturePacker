#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>

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

private:
    SettingsVO  m_svo;
};

#endif // PUBLISHER_H
