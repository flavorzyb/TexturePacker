#include <QFileDialog>

#include "include/viewwindow.h"
#include "include/utils.h"

ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initStatusBar();
    initAction();
    initMenu();
    initInfoList();
    initViewArea();
    initBottom();
    initUI();
}

void ViewWindow::onFileAction()
{
    QFileDialog fd(this, "选取要查看的BIP文件");
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setFilter(QDir::Files);
    fd.setNameFilter("*.bip");
    if (fd.exec())
    {
        QStringList filenames = fd.selectedFiles();
        for (int var = 0; var < filenames.size(); ++var)
        {
            printf("file:%s\n", filenames.at(var).toStdString().c_str());
        }

    }
}

void ViewWindow::initUI()
{
    setWindowTitle("资源查看器");
    setMinimumSize(800, 600);

    m_wWindow = new QWidget(this);
    setCentralWidget(m_wWindow);

    QGridLayout * layout = new QGridLayout;
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(30);

    layout->setColumnStretch(0, 3);
    layout->setColumnStretch(1, 7);

    layout->addWidget(m_lwInfoList);

    layout->addWidget(m_sViewScroll);

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
    m_lbStatusBar = new QLabel;
    m_lbStatusBar->setText("状态栏: 准备就绪");
    m_lbStatusBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_lbStatusBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    statusBar()->addWidget(m_lbStatusBar);
}

void ViewWindow::initInfoList()
{
    m_lwInfoList = new QListWidget;
    QListWidgetItem *item = new QListWidgetItem;
    item->setText("aaaaaaaa");
    item->setStatusTip("bbbbbb");
    m_lwInfoList->addItem(item);

    item = new QListWidgetItem;
        item->setText("ccccccc");
        item->setStatusTip("bbbbbb");
        m_lwInfoList->addItem(item);

        item = new QListWidgetItem;
            item->setText("aaaaddddddaaaa");
            item->setStatusTip("bbbbbb");
            m_lwInfoList->addItem(item);

}

void ViewWindow::initViewArea()
{
    m_sViewScroll = new QScrollArea;
}

void ViewWindow::initBottom()
{

}
