#include <QImage>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "include/fileutils.h"
#include "include/s3tcencode.h"
#include "include/imageutils.h"

S3TCEncode::S3TCEncode()
{
}

S3TCEncode::~S3TCEncode()
{
}

S3TC * S3TCEncode::convert(const QString & imagePath)
{
    unsigned long size = 0;
    unsigned char * data = FileUtils::getFileData(imagePath, "rb", &size);
    if ((NULL == data) || (0 == size))
    {
        return NULL;
    }

    QImage image;
    if (!image.loadFromData(data, size, "PNG"))
    {
        delete [] data;
        return NULL;
    }

    S3TC * result = convert(data, size, image.width(), image.height());
    delete [] data;

    return result;
}

S3TC * S3TCEncode::convert(const unsigned char * data, unsigned long size, unsigned int width, unsigned int height)
{
    if ((NULL == data) || (0 == size))
    {
        return NULL;
    }

    if ((false == ImageUtils::isPowOf2(width))
            || (false == ImageUtils::isPowOf2(height))
       )
    {
        return NULL;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "OPENGL_INIT: Video initialization failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void S3TCEncode::init()
{

}
