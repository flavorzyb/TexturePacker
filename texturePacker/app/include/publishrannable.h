#ifndef PUBLISHRANNABLE_H
#define PUBLISHRANNABLE_H

#include <QRunnable>
#include <QObject>

#include "common/include/settingsvo.h"
#include "common/include/publisher.h"

class PublishRannable : public QRunnable
{
public:
    explicit PublishRannable(const SettingsVO & svo);
    virtual ~PublishRannable();
    void run();

signals:
    void update(QString info);
    void finished();

private:
    SettingsVO m_svo;
    Publisher * m_publish;
};

#endif // PUBLISHRANNABLE_H
