#ifndef PNG_H
#define PNG_H
#include "include/image.h"
#include "include/pvr.h"

class PNG : public Image
{
    Q_OBJECT
public:
    PNG();
    PNG(const QString & filename);
    virtual ~PNG();
    virtual bool load();
    PVR * convertToPVR();
    virtual bool save(const QString & filename);
private:
    int findFirstHorizontalNoBlank();
    int findLastHorizontalNoBlank();
    int findFirstVerticalNoBlank();
    int findLastVerticalNoBlank();

private:
    QImage * m_pImg;
};

#endif // PNG_H
