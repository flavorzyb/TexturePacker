#include "mainwindow.h"
#include <QVBoxLayout>
#include <QtWidgets>


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
    lbInput->setAlignment(Qt::AlignRight);

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

    m_gbInputGroup->setLayout(layout);
}

void MainWindow::initOutputGroup()
{

}

void MainWindow::initOpGroup()
{
}
