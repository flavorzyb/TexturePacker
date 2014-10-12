#include <QFileDialog>
#include <QFileInfo>

#include "include/viewwindow.h"
#include "include/utils.h"
#include "common/include/bipreader.h"

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

bool ViewWindow::loadFile(const QString &filePath)
{
    if (filePath.toLower().endsWith(".bip"))
    {
        QFileInfo fileInfo(filePath);
        char strSize[64] = {0};
        snprintf(strSize, sizeof(strSize), "%.2fKB (%lld bytes)", fileInfo.size() * 1.0f / 1024, fileInfo.size());
        m_lbStatusBar->setText("文件名: " + fileInfo.fileName() + "    文件大小: " + strSize);
        BipReader reader(filePath);
        PVR * pvr = reader.load();
        m_lwInfoList->clear();
        const QVector<FrameVO> framelists = pvr->imagevo().frames();

        QVector<FrameVO>::const_iterator iterator = framelists.begin();
        for (; iterator != framelists.end(); iterator++)
        {
            m_lwInfoList->addItem(iterator->name());
        }
    }
    return false;
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
        for (int i = 0; i < filenames.size(); ++i)
        {
            loadFile(filenames.at(i));
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

    layout->setColumnStretch(0, 25);
    layout->setColumnStretch(1, 75);

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
}

void ViewWindow::initViewArea()
{
    m_sViewScroll = new QScrollArea;
    QImage image("/Users/flavor/tmp/zw_bs.png");
//    image = image.scaled(image.width() * 2, image.height() * 2);
    m_lbViewContent = new QLabel;
    m_lbViewContent->setPixmap(QPixmap::fromImage(image));
    m_sViewScroll->setWidget(m_lbViewContent);
}

void ViewWindow::initBottom()
{
}
