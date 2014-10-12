#include <QFileDialog>
#include <QFileInfo>

#include "include/viewwindow.h"
#include "include/utils.h"
#include "common/include/bipreader.h"
#include "common/include/png.h"
#include "common/include/pvr.h"

ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initStatusBar();
    initInfoList();
    initViewArea();
    initBottom();
    initUI();
    initAction();
    initMenu();
}

bool ViewWindow::loadFile(const QString &filePath)
{
    if (filePath.toLower().endsWith(".bip"))
    {
        m_lwInfoList->clear();

        QFileInfo fileInfo(filePath);
        BipReader reader(filePath);
        PVR * pvr = reader.load();
        if (NULL == pvr)
        {
            return false;
        }

        char strSize[1024] = {0};
        snprintf(strSize,
                 sizeof(strSize),
                 "文件名: %s    文件大小: %.2fKB (%lld bytes)    宽: %d  高: %d",
                 fileInfo.fileName().toStdString().c_str(),
                 fileInfo.size() * 1.0f / 1024,
                 fileInfo.size(),
                 pvr->width(),
                 pvr->height());

        m_lbStatusBar->setText(strSize);

        const QVector<FrameVO> framelists = pvr->imagevo().frames();
        QVector<FrameVO>::const_iterator iterator = framelists.begin();
        for (; iterator != framelists.end(); iterator++)
        {
            m_lwInfoList->addItem(iterator->name());
        }

        PNG * png = pvr->convertToPng();
        if (png && png->getImage())
        {
            m_viewImage = *(png->getImage());
            m_lbViewScene->clear();
            m_lbViewScene->addPixmap(QPixmap::fromImage(m_viewImage));
            m_lbViewContent->setMinimumSize(m_viewImage.width() + 10, m_viewImage.height() + 10);
            m_scaleValue = 1;
        }

        delete png;
        delete pvr;
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

void ViewWindow::onSpinBoxValueChanged(double value)
{
    m_sMagnificationSlider->setValue(value * 10);
    onMagnificationImage();
}

void ViewWindow::onSliderValueChanged(int value)
{
    m_sbMagnificationBox->setValue(value * 1.0f / 10);
    onMagnificationImage();
}

void ViewWindow::initUI()
{
    setWindowTitle("资源查看器");
    setMinimumSize(1000, 800);

    m_wWindow = new QWidget(this);
    setCentralWidget(m_wWindow);

    QGridLayout * layout = new QGridLayout;
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(30);

    layout->setColumnStretch(0, 2);
    layout->setColumnStretch(1, 8);

    layout->addWidget(m_lwInfoList, 0, 0);

    layout->addWidget(m_lbViewContent, 0, 1);

    layout->addWidget(m_gbMagnification, 1, 0, 1, 2);

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

    connect(m_sbMagnificationBox, SIGNAL(valueChanged(double)), this, SLOT(onSpinBoxValueChanged(double)));
    connect(m_sMagnificationSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
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
    m_lbViewScene   = new QGraphicsScene;
    m_lbViewContent = new QGraphicsView(m_lbViewScene);
}

void ViewWindow::initBottom()
{
    m_gbMagnification = new QGroupBox;
    m_gbMagnification->setTitle("放大/缩小");

    m_sbMagnificationBox = new QDoubleSpinBox;
    m_sbMagnificationBox->setMinimum(0.1);
    m_sbMagnificationBox->setMaximum(10.0);
    m_sbMagnificationBox->setMinimumWidth(100);
    m_sbMagnificationBox->setSingleStep(0.1);
    m_sbMagnificationBox->setAlignment(Qt::AlignRight);
    m_sbMagnificationBox->setValue(1.0);

    m_sbMagnificationBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_sMagnificationSlider = new QSlider;
    m_sMagnificationSlider->setOrientation(Qt::Horizontal);
    m_sMagnificationSlider->setMinimum(1);
    m_sMagnificationSlider->setMaximum(100);
    m_sMagnificationSlider->setValue(10);
    m_sMagnificationSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(m_sbMagnificationBox);
    layout->addWidget(m_sMagnificationSlider);

    m_gbMagnification->setLayout(layout);
}

void ViewWindow::onMagnificationImage()
{
    if (m_viewImage.width() > 0)
    {
        m_lbViewContent->scale(1.0 / m_scaleValue, 1.0 / m_scaleValue);
        m_scaleValue = m_sbMagnificationBox->value();
        m_lbViewContent->scale(m_scaleValue, m_scaleValue);
    }
}
