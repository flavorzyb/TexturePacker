#ifndef PVR_H
#define PVR_H

#include "include/image.h"
#include "include/PVRTDecompress.h"
#include "include/PVRTexture.h"
#include "include/PVRTextureUtilities.h"

class PVR : public Image
{
public:
    PVR();
    PVR(QString filename);
    PVR(const PVR & pvr);
    virtual ~PVR();
    virtual bool load();

private:
    pvrtexture::CPVRTexture * m_pvrTexture;
};

#endif // PVR_H
