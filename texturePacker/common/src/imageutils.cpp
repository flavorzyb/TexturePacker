#include <exception>
#include "include/imageutils.h"

ImageUtils::ImageUtils()
{
}

ImageUtils::~ImageUtils()
{

}

int ImageUtils::getMinPowOf2(int value)
{
    if (value < 1)
    {
        return -1;
    }

    int result = 1;
    for (int i = 0; i < 11; i++)
    {
        result *= 2;
        if (result >= value)
        {
            return result;
        }
    }

    return -1;
}

bool ImageUtils::isPowOf2(int value)
{
    if (value < 2)
    {
        return false;
    }

    int result = 1;
    for (int i = 0; i < 11; ++i)
    {
        result *= 2;

        if (result == value)
        {
            return true;
        }
    }

    return false;
}
