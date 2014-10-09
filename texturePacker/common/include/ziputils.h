#ifndef ZIPUTILS_H
#define ZIPUTILS_H

#include <QObject>

struct CCZHeader {
        unsigned char   sig[4];             // signature. Should be 'CCZ!' 4 bytes
        unsigned short  compression_type;   // should 0
        unsigned short  version;            // should be 2 (although version type==1 is also supported)
        unsigned int    reserved;           // Reserved for users.
        unsigned int    len;                // size of the uncompressed file
    };

    enum {
        CCZ_COMPRESSION_ZLIB,               // zlib format.
        CCZ_COMPRESSION_BZIP2,              // bzip2 format (not supported yet)
        CCZ_COMPRESSION_GZIP,               // gzip format (not supported yet)
        CCZ_COMPRESSION_NONE,               // plain (not supported yet)
    };

class ZipUtils : public QObject
{
    Q_OBJECT
public:
    ZipUtils();
    static int ccInflateCCZFile(const char *filename, unsigned char **out);
    static int ccInflateCCZData(const unsigned char *compressed, unsigned int dataLen, unsigned char **out);
    static bool ccDeflateCCZFile(const char * filename, unsigned char * data, unsigned long dataLen);
    static int ccDeflateCCZData(unsigned char * data, unsigned long dataLen, unsigned char **out);
};

#endif // ZIPUTILS_H
