#include <QFileDialog>
#include <QThreadPool>

#include "include/mainwindow.h"
#include "include/aboutme.h"
#include "include/utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initInputSettingsGroup();
    initOutputSettingGroup();
    initOpGroup();
    initOutputGroup();
    initUI();
    initAction();
    initMenu();
    initStatusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onPublishFinished()
{
     m_pbPublish->setEnabled(true);
}

void MainWindow::updatePublishInfo(QString info)
{
    if (info.length() > 0)
    {
        m_pteOutput->appendPlainText(info);
    }
}

void MainWindow::initUI()
{
    m_wMainWidget = new QWidget;
    //QWidget::setLayout: Attempting to set QLayout "" on MainWindow "", which already has a layout
    setCentralWidget(m_wMainWidget);

    setWindowTitle(tr("资源转换工具"));
    setMinimumSize(800, 600);

    QWidget * wBlank = new QWidget;
    wBlank->setMinimumSize(20, 10);
    wBlank->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(wBlank);
    mainLayout->addWidget(m_gbInputSettingGroup);
    mainLayout->addWidget(m_gbOutputSettingGroup);
    mainLayout->addWidget(m_gbOpGroup);
    mainLayout->addWidget(m_gbOutputGroup);

    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(30);

    m_wMainWidget->setLayout(mainLayout);

    if (!isFullScreen())
    {
        Utils::center(this);
    }
}

void MainWindow::initMenu()
{
    m_mAboutMe = menuBar()->addMenu("帮助(&H)");
    m_mAboutMe->addAction(m_aAboutMe);
}

void MainWindow::initAction()
{
    m_aAboutMe = new QAction(tr("关于我(&A)"), this);
    m_aAboutMe->setStatusTip(tr("关于软件的一些说明"));
    connect(m_aAboutMe, SIGNAL(triggered()), this, SLOT(onAboutMeAction()));
}

void MainWindow::initStatusBar()
{
    m_lbStatusBar = new QLabel;
    m_lbStatusBar->setText("状态栏: 准备就绪");
    m_lbStatusBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_lbStatusBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    statusBar()->addWidget(m_lbStatusBar);
}

void MainWindow::onAboutMeAction()
{
    AboutMe am(this);
    am.exec();
}

void MainWindow::initInputSettingsGroup()
{
    m_gbInputSettingGroup = new QGroupBox;
    m_gbInputSettingGroup->setTitle(tr("输入设置"));
    m_gbInputSettingGroup->setAutoFillBackground(true);

    QGridLayout * layout = new QGridLayout();

    QLabel * lbInput = new QLabel;
    lbInput->setText(tr("输入路径:"));
    lbInput->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    m_leInputSettingPath = new QLineEdit;
    m_leInputSettingPath->setText(tr("请设置输入路径"));
    m_leInputSettingPath->setReadOnly(true);

    m_pbInputSettingPath = new QPushButton;
    m_pbInputSettingPath->setText(tr("设置输入目录"));
    m_pbInputSettingPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pbInputSettingPath->setStatusTip(tr("设置资源转换的输入目录"));
    connect(m_pbInputSettingPath, SIGNAL(clicked()), this, SLOT(onSettingInputPathEvent()));

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 6);
    layout->setColumnStretch(2, 2);

    layout->addWidget(lbInput, 0, 0);
    layout->addWidget(m_leInputSettingPath, 0, 1);
    layout->addWidget(m_pbInputSettingPath, 0, 2);

    m_gbInputSettingGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_gbInputSettingGroup->setLayout(layout);
}

void MainWindow::initOutputSettingGroup()
{
    m_gbOutputSettingGroup = new QGroupBox;
    m_gbOutputSettingGroup->setTitle(tr("输出设置"));
    m_gbOutputSettingGroup->setAutoFillBackground(true);

    QLabel * lbFormat = new QLabel;
    lbFormat->setText("输出格式:");
    lbFormat->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    QButtonGroup * btnGroup = new QButtonGroup;

    m_rbtnIOS = new QRadioButton;
    m_rbtnIOS->setText(tr("IOS资源格式"));
    m_rbtnIOS->setChecked(true);
    m_rbtnIOS->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_rbtnIOS->setStatusTip(tr("将资源转换的格式设置为IOS专用格式"));

    m_rbtnAndroid = new QRadioButton;
    m_rbtnAndroid->setText(tr("Android资源格式"));
    m_rbtnAndroid->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_rbtnAndroid->setStatusTip(tr("将资源转换的格式设置为Android专用格式"));

    btnGroup->addButton(m_rbtnIOS);
    btnGroup->addButton(m_rbtnAndroid);

    QHBoxLayout * lyFormat = new QHBoxLayout;
    lyFormat->addWidget(m_rbtnIOS);
    lyFormat->addWidget(m_rbtnAndroid);

    QWidget * wFormat = new QWidget;
    wFormat->setLayout(lyFormat);
    //wFormat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel * lbInput = new QLabel;
    lbInput->setText(tr("输出路径:"));
    lbInput->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    m_leOutputSettingPath = new QLineEdit;
    m_leOutputSettingPath->setText(tr("请设置输出路径"));
    m_leOutputSettingPath->setReadOnly(true);

    m_pbOutputSettingPath = new QPushButton;
    m_pbOutputSettingPath->setText(tr("设置输出目录"));
    m_pbOutputSettingPath->setStatusTip(tr("设置资源转换的输出目录"));
    m_pbOutputSettingPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_pbOutputSettingPath, SIGNAL(clicked()), this, SLOT(onSettingOutputPathEvent()));

    QGridLayout * layout = new QGridLayout;
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 6);
    layout->setColumnStretch(2, 2);

    layout->addWidget(lbFormat, 0, 0);
    layout->addWidget(wFormat, 0, 1, 1, 2);

    layout->addWidget(lbInput, 1, 0);
    layout->addWidget(m_leOutputSettingPath, 1, 1);
    layout->addWidget(m_pbOutputSettingPath, 1, 2);

    m_gbOutputSettingGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_gbOutputSettingGroup->setLayout(layout);
}

void MainWindow::initOpGroup()
{
    m_gbOpGroup = new QGroupBox;
    m_gbOpGroup->setTitle("操作");
    m_gbOpGroup->setAutoFillBackground(true);

    m_pbPublish = new QPushButton;
    m_pbPublish->setText(tr("导出"));
    m_pbPublish->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_pbClosed  = new QPushButton;
    m_pbClosed->setText(tr("关闭"));
    m_pbClosed->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(m_pbPublish, SIGNAL(clicked()), this, SLOT(onPublishEvent()));
    connect(m_pbClosed, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(m_pbPublish);
    layout->addWidget(m_pbClosed);

    m_gbOpGroup->setLayout(layout);
}

void MainWindow::initOutputGroup()
{
    m_gbOutputGroup = new QGroupBox;
    m_gbOutputGroup->setTitle(tr("输出"));

    m_pteOutput = new QPlainTextEdit;
    m_pteOutput->setReadOnly(true);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_pteOutput);

    m_gbOutputGroup->setLayout(layout);
}

void MainWindow::onSettingInputPathEvent()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("选择输入目录"));
    if (dirPath.length() > 0)
    {
        m_settingsvo.setInputPath(dirPath);
        m_leInputSettingPath->setText(dirPath);
    }
}

void MainWindow::onSettingOutputPathEvent()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("选择输出目录"));
    if (dirPath.length() > 0)
    {
        m_settingsvo.setOutputPath(dirPath);
        m_leOutputSettingPath->setText(dirPath);
    }
}

void MainWindow::onPublishEvent()
{
    if (m_rbtnIOS->isChecked())
    {
        m_settingsvo.setFormat(SettingsVO::IOS);
    }
    else
    {
        m_settingsvo.setFormat(SettingsVO::ANDROID);
    }

    m_pbPublish->setEnabled(false);
    m_pteOutput->clear();

    m_publish.setSettingsVO(m_settingsvo);
    connect(&m_publish, SIGNAL(update(QString)), this, SLOT(updatePublishInfo(QString)));
    connect(&m_publish, SIGNAL(finished()), this, SLOT(onPublishFinished()));
    m_publish.start();
}
