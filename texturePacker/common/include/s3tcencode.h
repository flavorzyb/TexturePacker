#ifndef S3TCENCODE_H
#define S3TCENCODE_H
#include <QString>

#include "include/s3tc.h"

class S3TCEncode
{
public:
    S3TCEncode();
    virtual ~S3TCEncode();
    S3TC * convert(const QString & imagePath);
    S3TC * convert(const unsigned char * data, unsigned long size, unsigned int width, unsigned int height);
private:
    S3TCEncode(const S3TCEncode & encode);
    S3TCEncode & operator = (const S3TCEncode & encode);

private:
    void initSDL();
};

#endif // S3TCENCODE_H
