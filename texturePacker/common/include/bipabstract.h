#ifndef BIPABSTRACT_H
#define BIPABSTRACT_H

#include <QObject>

class BipAbstract : public QObject
{
    Q_OBJECT
public:
    explicit BipAbstract(QObject *parent = 0);

signals:

public slots:

};

#endif // BIPABSTRACT_H
