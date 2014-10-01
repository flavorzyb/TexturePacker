#include <QtWidgets>
#include "include/aboutme.h"
#include "common/include/config.h"
#include "include/utils.h"

AboutMe::AboutMe(QWidget *parent) :
    QDialog(parent, Qt::Dialog)
{
    initUI();
}

void AboutMe::initUI()
{
    setWindowTitle(tr("关于我"));
    setMinimumSize(400, 200);

    QFont font;
    font.setPointSize(22);

    QLabel *lbName = new QLabel;
    lbName->setText(tr("资源转换工具"));
    lbName->setFont(font);
    lbName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *lbAuthor = new QLabel;
    lbAuthor->setText(tr("作者: ") + Config::AUTHOR);
    lbAuthor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *lbVersion = new QLabel;
    lbVersion->setText(tr("版本: ") + Config::VERSION);
    lbVersion->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *lbDate = new QLabel;
    lbDate->setText(tr("时间: ") + Config::DATE);
    lbDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *pbClosed = new QPushButton;
    pbClosed->setText(tr("关闭"));
    pbClosed->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(pbClosed, SIGNAL(clicked()), this, SLOT(close()));

    QWidget *wBlank = new QWidget;
    wBlank->setMinimumSize(20, 10);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(lbName);
    layout->addWidget(lbAuthor);
    layout->addWidget(lbVersion);
    layout->addWidget(lbDate);
    layout->addWidget(pbClosed);
    layout->addWidget(wBlank);

    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(30);

    setLayout(layout);

    Utils::center(this);
}
