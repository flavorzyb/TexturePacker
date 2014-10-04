#ifndef PVRPNG_H
#define PVRPNG_H

#include "include/pvrabstract.h"

class PVRPNG : public PVRAbstract
{
public:
    PVRPNG();
    PVRPNG(QString filename);
    virtual bool load();
    bool save2Pvr();
};

#endif // PVRPNG_H
