#ifndef PVR_H
#define PVR_H

#include "include/image.h"

class PVR : public Image
{
public:
    PVR();
    PVR(QString filename);
    PVR(const PVR & pvr);
    virtual bool load();
};

#endif // PVR_H
