#include "include/tpapplication.h"
TpApplication::TpApplication(int &argc, char **argv):QApplication(argc, argv)
{
}

TpApplication::~TpApplication()
{
}

void TpApplication::initMainWindow()
{
//    m_mainWindow.show();
    m_viewWindow.show();
}

#if defined(Q_OS_OSX)
bool TpApplication::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::FileOpen:
//        if (!m_mainWindows.isEmpty()) {
//            mainWindow()->loadPage(static_cast<QFileOpenEvent *>(event)->file());
//            return true;
//        }
    default:
        break;
    }

    return QApplication::event(event);
}
#endif
