#ifndef BIPIMAGE_H
#define BIPIMAGE_H
#include "include/image.h"
#include "include/imagevo.h"

class BipImage : public Image
{
public:
    BipImage();
    BipImage(const QString & filename);
    virtual ~BipImage();
    virtual bool loadData(const unsigned char * pData, unsigned long size) = 0;
    virtual bool loadCCZData(const unsigned char * pData, unsigned long size) = 0;
    virtual bool save(const QString & filename) = 0;
    virtual bool saveCCZ(const QString & filename) = 0;
    virtual unsigned char * saveCCZToBuffer(unsigned long *size) = 0;
    virtual bool isEmpty() const;
    const ImageVO getImageVO() const;
    void setImageVO(const ImageVO & imagevo);
private:
    ImageVO m_imagevo;
};

#endif // BIPIMAGE_H
