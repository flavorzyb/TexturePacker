#ifndef PNG_H
#define PNG_H
#include "include/image.h"
#include "include/pvr.h"

class PNG : public Image
{
    Q_OBJECT
public:
    PNG();
    PNG(QString filename);
    virtual ~PNG();
    virtual bool load();
    PVR convertToPVR();
private:
    QImage * m_pImg;
};

#endif // PNG_H
