#ifndef PUBLISHRANNABLE_H
#define PUBLISHRANNABLE_H

#include <QRunnable>

#include "common/include/settingsvo.h"
#include "common/include/publisher.h"
#include "include/mainwindow.h"

class PublishRannable : public QRunnable
{
public:
    explicit PublishRannable(const SettingsVO & svo, MainWindow * mw);
    virtual ~PublishRannable();
    void run();

private:
    SettingsVO m_svo;
    Publisher * m_publish;
    MainWindow *m_mainWindow;
};

#endif // PUBLISHRANNABLE_H
