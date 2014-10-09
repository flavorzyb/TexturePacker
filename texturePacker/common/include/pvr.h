#ifndef PVR_H
#define PVR_H

#include "include/image.h"
#include "include/PVRTDecompress.h"
#include "include/PVRTexture.h"
#include "include/PVRTextureUtilities.h"
#include "include/imagevo.h"

class PVR : public Image
{
public:
    PVR();
    PVR(const QString & filename);
    PVR(const PVR & pvr);
    virtual ~PVR();
    virtual bool load();
    bool loadData(const unsigned char * pData, unsigned long size);
    bool loadCCZData(const unsigned char * pData, unsigned long size);
    virtual bool save(const QString & filename);
    bool saveCCZ(const QString & filename);

    ImageVO imagevo() const;
    void setImagevo(const ImageVO & imagevo);

    inline bool isEmpty() const { return (NULL == m_pvrTexture);}
private:
    bool isPVRCCZFile(const QString & filename) const;
    bool loadPVRCCZ(const QString & filename);
    bool loadPVR(const QString & filename);
private:
    pvrtexture::CPVRTexture * m_pvrTexture;
    ImageVO m_imagevo;
};

#endif // PVR_H
