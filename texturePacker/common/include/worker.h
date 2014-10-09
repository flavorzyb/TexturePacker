#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker();
    void run();
signals:

public slots:

};

#endif // WORKER_H
