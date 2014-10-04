#ifndef PNG_H
#define PNG_H
#include "include/image.h"

class PNG : public Image
{
    Q_OBJECT
public:
    PNG();
    PNG(QString filename);
    virtual ~PNG();
    virtual bool load();
signals:

public slots:

private:
    QImage * m_pImg;
};

#endif // PNG_H
