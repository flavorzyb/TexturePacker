#include <QRgb>

#include "include/png.h"
#include "include/imageutils.h"
#include "include/fileutils.h"

PNG::PNG():Image()
    , m_pImg(NULL)
{
}

PNG::PNG(const QString & filename):Image(filename)
    , m_pImg(NULL)
{
}

PNG::~PNG()
{
    if (m_pImg != NULL)
    {
        delete m_pImg;
    }
}

bool PNG::load()
{
    if (!exists(filePath()))
    {
        return false;
    }

    if (m_pImg != NULL)
    {
        delete m_pImg;
    }

    m_pImg = new QImage(filePath(), "PNG");
    setWidth(m_pImg->width());
    setHeight(m_pImg->height());

    return true;
}

bool PNG::loadData(const unsigned char *pData, int width, int height)
{
    if (m_pImg != NULL)
    {
        delete m_pImg;
    }

    setWidth(width);
    setHeight(height);

    m_pImg = new QImage(pData, width, height, QImage::Format_RGBA8888);

    return true;
}

PVR * PNG::convertToPVR()
{
    if (m_pImg == NULL)
    {
        return NULL;
    }

    QRect cropRect = findCropRect();

    int fnw = cropRect.x();
    int lnw = cropRect.width();

    int fnh = cropRect.y();
    int lnh = cropRect.height();

    // if image is blank
    if (fnw >= lnw)
    {
        fnw = 0;
        lnw = width() - 1;
    }

    if (fnh >= lnh)
    {
        fnh = 0;
        lnh = height() - 1;
    }

    int w = lnw + 1 - fnw;
    int h = lnh + 1 - fnh;

    int pw = ImageUtils::getMinPowOf2(w);
    int ph = ImageUtils::getMinPowOf2(h);

    if (pw > ph)
    {
        ph = pw;
    }
    else
    {
        pw = ph;
    }

    int windex = (((pw - 2) > w) ? 2 : 0);
    int hindex = (((ph - 2) > h) ? 2 : 0);

    unsigned char * pImageData = createImageData(fnw, fnh, w, h, pw, ph, windex, hindex);
    if (pImageData != NULL)
    {
        pvrtexture::CPVRTextureHeader header(pvrtexture::PVRStandard8PixelType.PixelTypeID, pw, ph);
        pvrtexture::CPVRTexture pvrTexture(header, pImageData);
        delete [] pImageData;
        pvrtexture::PixelType pvrTC4BPP_RGB(ePVRTPF_PVRTCI_4bpp_RGBA);
        QString pvrFile = FileUtils::createImageTempFolder() + "/" + FileUtils::getRandFileNameString() + ".pvr";

        if (pvrtexture::Transcode(pvrTexture, pvrTC4BPP_RGB, ePVRTVarTypeUnsignedByteNorm, ePVRTCSpacelRGB, pvrtexture::ePVRTCBest, false) && pvrTexture.saveFile(pvrFile.toStdString().c_str()))
        {
            ImageVO ivo(pw, ph);
            ivo.setFileName(filePath());
            FrameVO frame(width(), height());
            frame.setName(filePath());
            frame.setMd5String(FileUtils::md5File(filePath()));
            frame.setRect(windex, hindex, w, h);
            int ox = w / 2 - width() / 2 + fnw;
            int oy = height() / 2 - fnh - h /2;
            frame.setOffset(ox, oy);
            frame.setSourceColorRect(fnw, fnh, w, h);

            ivo.addFrame(frame);

            PVR * result = new PVR(pvrFile);
            result->setImagevo(ivo);

            result->load();
            FileUtils::unlink(pvrFile);

            return result;
        }
    }

    return NULL;
}

unsigned char *PNG::createImageData(int fnw,  int fnh, int w, int h, int pw, int ph, int windex, int hindex)
{
    if (m_pImg == NULL)
    {
        return NULL;
    }

    int len = 4 * pw * ph;
    if (len < 4)
    {
        return NULL;
    }

    unsigned char * pImageData = new unsigned char [len];
    memset(pImageData, 0, len * sizeof(unsigned char));


    for(int x = windex; x < (windex + w); x++)
    {
        for (int y = hindex; y < (hindex + h); y++)
        {
            QRgb v = m_pImg->pixel(x + fnw - windex, y + fnh - hindex);
            pImageData[4 * (y * pw + x)    ] = qRed(v);
            pImageData[4 * (y * pw + x) + 1] = qGreen(v);
            pImageData[4 * (y * pw + x) + 2] = qBlue(v);
            pImageData[4 * (y * pw + x) + 3] = qAlpha(v);
        }
    }

    return pImageData;
}

bool PNG::save(const QString &filename)
{
    if (m_pImg == NULL)
    {
        return false;
    }

    return m_pImg->save(filename, "PNG");
}

QRect PNG::findCropRect()
{
    if (m_pImg == NULL)
    {
        return QRect(0, 0, 0, 0);
    }

    int minx = 999999;
    int miny = 999999;
    int maxx = 0;
    int maxy = 0;

    for (int x = 0; x < width(); ++x)
    {
        for (int y = 0; y < height(); ++y)
        {
            if (qAlpha(m_pImg->pixel(x, y)) != 0)
            {
                if (minx > x)
                {
                    minx = x;
                }

                if (miny > y)
                {
                    miny = y;
                }

                if (maxx < x)
                {
                    maxx = x;
                }

                if (maxy < y)
                {
                    maxy = y;
                }
            }
        }
    }

    return QRect(minx, miny, maxx, maxy);
}

ETC * PNG::convertToETC()
{
    QString imagePath = filePath();
    if (imagePath.length() < 1)
    {
        imagePath = FileUtils::createImageTempFolder() + "/" + FileUtils::getRandFileNameString() + ".png";
        if (save(path) == false)
        {
            return NULL;
        }
    }


    return NULL;
}
