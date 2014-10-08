#include "include/png.h"
#include "include/imageutils.h"

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

    int w = lnw + 1 - fnw;
    int h = lnh + 1 - fnh;

    int pw = ImageUtils::getMinPowOf2(w);
    int ph = ImageUtils::getMinPowOf2(h);


    QImage image(pw, ph, m_pImg->format());
    int windex = ((pw - 2) > w) ? 2 : 0;
    int hindex = ((ph - 2) > h) ? 2 : 0;

    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            image.setPixel(i+windex, j+hindex, m_pImg->pixel(i+fnw, j+fnh));
        }
    }

    image.save("output/yezhi.png");

    return NULL;
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
