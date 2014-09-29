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
    setMinimumSize(600, 400);

    QLabel *lbName = new QLabel();
    lbName->setText(tr("资源转换工具"));

    QString str =tr("作者:");
    str += Config::AUTHOR;

    QLabel *lbAuthor = new QLabel();
    lbAuthor->setText(str);

    str = tr("版本:");
    str += Config::VERSION;

    QLabel *lbVersion = new QLabel();
    lbVersion->setText(str);

    str = tr("时间:");
    str += Config::DATE;

    QLabel *lbDate = new QLabel();
    lbDate->setText(str);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(lbName);
    layout->addWidget(lbAuthor);
    layout->addWidget(lbVersion);
    layout->addWidget(lbDate);

    setLayout(layout);
}
