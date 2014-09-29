#include "mainwindow.h"
#include <QVBoxLayout>
#include <QtWidgets>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initInputGroup();
    initOutputGroup();
    initOpGroup();
    initUI();
    initAction();
    initMenu();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    m_wMainWidget = new QWidget();
    //QWidget::setLayout: Attempting to set QLayout "" on MainWindow "", which already has a layout
    setCentralWidget(m_wMainWidget);

    setWindowTitle(tr("资源转换工具"));
    setMinimumSize(800, 600);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_gbInputGroup);
    mainLayout->addWidget(m_gbOutputGroup);
    mainLayout->addWidget(m_gbOpGroup);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(30);

    m_wMainWidget->setLayout(mainLayout);
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

void MainWindow::onAboutMeAction()
{
    printf("onAboutMeAction.......\n");
}

void MainWindow::initInputGroup()
{
    m_gbInputGroup = new QGroupBox();
    m_gbInputGroup->setTitle(tr("输入设置"));

    QGridLayout * layout = new QGridLayout();

    QLabel * lbInput = new QLabel();
    lbInput->setText(tr("输入路径:"));
    lbInput->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    m_leInputDirPath = new QLineEdit();
    m_leInputDirPath->setText(tr("请设置输入路径"));
    m_leInputDirPath->setReadOnly(true);

    m_pbInputDirPath = new QPushButton();
    m_pbInputDirPath->setText(tr("设置输入目录"));
    m_pbInputDirPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 4);
    layout->setColumnStretch(2, 1);

    layout->addWidget(lbInput, 0, 0);
    layout->addWidget(m_leInputDirPath, 0, 1);
    layout->addWidget(m_pbInputDirPath, 0, 2);

    m_gbInputGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_gbInputGroup->setLayout(layout);
}

void MainWindow::initOutputGroup()
{
    m_gbOutputGroup = new QGroupBox();
    m_gbOutputGroup->setTitle(tr("输出设置"));

    QGridLayout * layout = new QGridLayout();

    QLabel * lbInput = new QLabel();
    lbInput->setText(tr("输出路径:"));
    lbInput->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    m_leOutputDirPath = new QLineEdit();
    m_leOutputDirPath->setText(tr("请设置输出路径"));
    m_leOutputDirPath->setReadOnly(true);

    m_pbOutputDirPath = new QPushButton();
    m_pbOutputDirPath->setText(tr("设置输出目录"));
    m_pbOutputDirPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 4);
    layout->setColumnStretch(2, 1);

    layout->addWidget(lbInput, 0, 0);
    layout->addWidget(m_leOutputDirPath, 0, 1);
    layout->addWidget(m_pbOutputDirPath, 0, 2);

    m_gbOutputGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_gbOutputGroup->setLayout(layout);
}

void MainWindow::initOpGroup()
{
    m_gbOpGroup = new QGroupBox();
    m_gbOpGroup->setTitle("操作");

    m_pbPublish = new QPushButton();
    m_pbPublish->setText(tr("导出"));
    m_pbPublish->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_pbClosed  = new QPushButton();
    m_pbClosed->setText(tr("关闭"));
    m_pbClosed->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    connect(m_pbClosed, SIGNAL(clicked()), this, SLOT(close()));

    QFormLayout * layout = new QFormLayout();
    layout->addRow(m_pbPublish, m_pbClosed);

    m_gbOpGroup->setLayout(layout);
}
