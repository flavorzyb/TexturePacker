#ifndef TPAPPLICATION_H
#define TPAPPLICATION_H

#include <QApplication>
#include "include/mainwindow.h"

class TpApplication : public QApplication
{
public:
    TpApplication(int &argc, char **argv);
    virtual ~TpApplication();
    void initMainWindow();

protected:
#if defined(Q_OS_OSX)
    bool event(QEvent* event);
#endif

private:
    MainWindow m_mainWindow;
};
#endif // TPAPPLICATION_H
