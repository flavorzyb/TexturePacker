#ifndef PVR_H
#define PVR_H

#include "include/bipimage.h"
#include "include/PVRTDecompress.h"
#include "include/PVRTexture.h"
#include "include/PVRTextureUtilities.h"

class PNG;

class PVR : public BipImage
{
public:
    PVR();
    PVR(const QString & filename);
    virtual ~PVR();
    virtual bool load();
    bool loadData(const unsigned char * pData, unsigned long size);
    bool loadCCZData(const unsigned char * pData, unsigned long size);
    virtual bool save(const QString & filename);
    unsigned char * saveToBuffer(unsigned long *size);
    bool saveCCZ(const QString & filename);
    unsigned char * saveCCZToBuffer(unsigned long *size);

    inline bool isEmpty() const { return (NULL == m_pvrTexture);}

    PNG * convertToPng();

private:
    PVR(const PVR & pvr);
    bool isPVRCCZFile(const QString & filename) const;
    bool loadPVRCCZ(const QString & filename);
    bool loadPVR(const QString & filename);
private:
    pvrtexture::CPVRTexture * m_pvrTexture;
};

#endif // PVR_H
