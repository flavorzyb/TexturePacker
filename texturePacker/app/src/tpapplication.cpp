#include "include/tpapplication.h"
TpApplication::TpApplication(int &argc, char **argv):QApplication(argc, argv)
{
}

TpApplication::~TpApplication()
{
}

void TpApplication::initMainWindow()
{
    m_mainWindow.setApp(this);
    m_mainWindow.show();
}

void TpApplication::showViewWindow()
{
    m_viewWindow.show();
}

#if defined(Q_OS_OSX)
bool TpApplication::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::FileOpen:
        m_viewWindow.show();
        m_viewWindow.loadFile(static_cast<QFileOpenEvent *>(event)->file());
        break;
    default:
        break;
    }

    return QApplication::event(event);
}
#endif
