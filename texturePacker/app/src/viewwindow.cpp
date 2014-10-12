#include "include/viewwindow.h"
#include "include/utils.h"

ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initStatusBar();
    initAction();
    initMenu();
    initUI();
}

void ViewWindow::onFileAction()
{
    printf("ffffffffffffff\n");
}

void ViewWindow::initUI()
{
    setWindowTitle("资源查看器");
    setMinimumSize(800, 600);

    m_wWindow = new QWidget(this);
    setCentralWidget(m_wWindow);

    QFormLayout * layout = new QFormLayout;
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(30);

    m_wWindow->setLayout(layout);

    if (!isFullScreen())
    {
        Utils::center(this);
    }
}

void ViewWindow::initMenu()
{
    m_mFile = this->menuBar()->addMenu("文件(&F)");
    m_mFile->addAction(m_aFile);
}

void ViewWindow::initAction()
{
    m_aFile = new QAction(tr("打开文件(&O)"), this);
    m_aFile->setStatusTip(tr("打开BIP文件"));
    m_aFile->setShortcut(QApplication::translate("ViewWindow", "Ctrl+O", 0));
    connect(m_aFile, SIGNAL(triggered()), this, SLOT(onFileAction()));
}

void ViewWindow::initStatusBar()
{
    statusBar();
}
