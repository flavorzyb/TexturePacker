#ifndef PNG_H
#define PNG_H
#include <QRect>
#include "include/image.h"
#include "include/pvr.h"
#include "include/etc.h"
#include "include/s3tc.h"

class PNG : public Image
{
public:
    PNG();
    PNG(const QString & filename);
    virtual ~PNG();
    virtual bool load();
    bool loadData(const unsigned char * pData, int width, int height);
    PVR * convertToPVR();
    ETC * convertToETC();
    S3TC * convertToS3TC();

    virtual bool save(const QString & filename);
    inline const QImage * getImage() const {return m_pImg;}
private:
    QRect findCropRect();
    unsigned char * createImageData(int fnw,  int fnh, int w, int h, int pw, int ph, int windex, int hindex);

private:
    QImage * m_pImg;
};

#endif // PNG_H
