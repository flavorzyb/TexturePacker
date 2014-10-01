#include <QApplication>
#include <QDesktopWidget>
#include "utils.h"


void Utils::center(QWidget *widget)
{
    if (widget == NULL) return ;

    widget->adjustSize();
    widget->move(QApplication::desktop()->screen()->rect().center() - widget->rect().center());
}
