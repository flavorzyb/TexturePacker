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
    PVR(const QString & filename);
    PVR(const PVR & pvr);
    virtual ~PVR();
    virtual bool load();
    virtual bool save(const QString & filename);
    bool saveCCZ(const QString & filename);

private:
    bool isPVRCCZFile(const QString & filename) const;
    bool loadPVRCCZ(const QString & filename);
    bool loadPVR(const QString & filename);
private:
    pvrtexture::CPVRTexture * m_pvrTexture;
};

#endif // PVR_H
