#ifndef BIPABSTRACT_H
#define BIPABSTRACT_H

#include "include/bipimage.h"

class BipAbstract
{
public:
    explicit BipAbstract();
    virtual ~BipAbstract();
    BipImage * getBipImage() const;
    void setBipImage(BipImage *img);
    bool isBipFile(const unsigned char * buffer, unsigned long size);
public:
    enum{HEAD_DATA_SIZE = 8};
    static const unsigned char BIP_HEAD_DATA[HEAD_DATA_SIZE];

private:
    BipAbstract(const BipAbstract & BipAbstract);
    const BipAbstract & operator = (const BipAbstract & bip);

private:
    BipImage * m_bipImage;
};

#endif // BIPABSTRACT_H
