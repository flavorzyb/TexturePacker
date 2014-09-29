#include <QtWidgets>
#include "aboutme.h"
#include "config.h"

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

    QLabel *lbName = new QLabel();
    lbName->setText(tr("资源转换工具"));
    lbName->setFont(font);
    lbName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString str =tr("作者:");
    str += Config::AUTHOR;

    QLabel *lbAuthor = new QLabel();
    lbAuthor->setText(str);
    lbAuthor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    str = tr("版本:");
    str += Config::VERSION;

    QLabel *lbVersion = new QLabel();
    lbVersion->setText(str);
    lbVersion->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    str = tr("时间:");
    str += Config::DATE;

    QLabel *lbDate = new QLabel();
    lbDate->setText(str);
    lbDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(lbName);
    layout->addWidget(lbAuthor);
    layout->addWidget(lbVersion);
    layout->addWidget(lbDate);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(30);

    setLayout(layout);
}
