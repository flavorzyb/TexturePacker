#include <QRgb>
#include "include/png.h"
#include "include/imageutils.h"
#include "include/fileutils.h"
#include "include/pvr.h"

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

    int fnw = findFirstHorizontalNoBlank();
    int lnw = findLastHorizontalNoBlank();

    int fnh = findFirstVerticalNoBlank();
    int lnh = findLastVerticalNoBlank();

    // if image is blank
    if (fnw== width())
    {
        fnw = 0;
        lnw = width() - 1;
    }

    if (fnh == height())
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

    int windex = ((pw - 2) > w) ? 2 : 0;
    int hindex = ((ph - 2) > h) ? 2 : 0;

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

    for (int x = 0; x < pw; ++x)
    {
        for (int y = 0; y < ph; ++y)
        {
           if ((x >= windex) &&
                   (y >= hindex) &&
                   ((x + fnw) < w) &&
                   ((y + fnh) < h))
           {
               QRgb v = m_pImg->pixel(x + fnw, y + fnh);
               pImageData[4 * (y * pw + x) + 0] = qRed(v);
               pImageData[4 * (y * pw + x) + 1] = qGreen(v);
               pImageData[4 * (y * pw + x) + 2] = qBlue(v);
               pImageData[4 * (y * pw + x) + 3] = qAlpha(v);
           }
           else
           {
               pImageData[4 * (y * pw + x) + 0] = 0;
               pImageData[4 * (y * pw + x) + 1] = 0;
               pImageData[4 * (y * pw + x) + 2] = 0;
               pImageData[4 * (y * pw + x) + 3] = 0;
           }
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

int PNG::findFirstHorizontalNoBlank()
{
    if (m_pImg == NULL)
    {
        return -1;
    }

    for (int w = 0; w < width(); w++)
    {
        for (int h = 0; h < height(); ++h)
        {
            if (qAlpha(m_pImg->pixel(w, h)) != 0)
            {
                return w;
            }
        }
    }

    return width();
}

int PNG::findLastHorizontalNoBlank()
{
    if (m_pImg == NULL)
    {
        return -1;
    }

    for (int w = width() - 1; w >= 0; w--)
    {
        for (int h = 0; h < height(); ++h)
        {
            if (qAlpha(m_pImg->pixel(w, h)) != 0)
            {
                return w;
            }
        }
    }

    return 0;
}

int PNG::findFirstVerticalNoBlank()
{
    if (m_pImg == NULL)
    {
        return -1;
    }

    for (int h = 0; h < height(); ++h)
    {
        for (int w = 0; w < width(); w++)
        {
            if (qAlpha(m_pImg->pixel(w, h)) != 0)
            {
                return h;
            }
        }
    }

    return height();
}

int PNG::findLastVerticalNoBlank()
{
    if (m_pImg == NULL)
    {
        return -1;
    }

    for (int h = height() - 1; h >=0; h--)
    {
        for (int w = 0; w < width(); w++)
        {
            if (qAlpha(m_pImg->pixel(w, h)) != 0)
            {
                return h;
            }
        }
    }

    return 0;
}
