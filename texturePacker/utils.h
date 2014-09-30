#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QWidget>

class Utils : public QObject
{
    Q_OBJECT
public:
    static void center(QWidget * widget);
signals:

public slots:

};

#endif // UTILS_H
