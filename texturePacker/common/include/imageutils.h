#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

class ImageUtils
{
public:
    static int getMinPowOf2(int value);
    static bool isPowOf2(int value);

private:
    ImageUtils();
    virtual ~ImageUtils();
};

#endif // IMAGEUTILS_H
