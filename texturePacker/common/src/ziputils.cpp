#include <zlib.h>

#include "include/ziputils.h"
#include "include/fileutils.h"
#include "include/macros.h"


ZipUtils::ZipUtils()
{
}

int ZipUtils::ccInflateCCZFile(const char *filename, unsigned char **out)
{
    if ((out == NULL) || (&*out == NULL))
    {
        return  -1;
    }

    unsigned long fileLen = 0;
    // load file into memory
    unsigned char* compressed = FileUtils::getFileData(filename, "rb", &fileLen);

    int len = ccInflateCCZData(compressed, fileLen, out);
    delete [] compressed;

    return len;
}

int ZipUtils::ccInflateCCZData(const unsigned char *compressed, unsigned int dataLen, unsigned char **out)
{
    if(NULL == compressed || 0 == dataLen)
    {
        return -1;
    }

    struct CCZHeader *header = (struct CCZHeader*) compressed;

    // verify header
    if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == '!' )
    {
        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 2 )
        {
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            return -1;
        }
    }
    else if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == 'p' )
    {
        // encrypted ccz file
        header = (struct CCZHeader*) compressed;

        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 0 )
        {
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    unsigned int len = CC_SWAP_INT32_BIG_TO_HOST( header->len);
    *out = (unsigned char*)malloc( len );
    if(! *out )
    {
        return -1;
    }

    unsigned long destlen = len;
    unsigned long source = (unsigned long) compressed + sizeof(*header);
    int ret = uncompress(*out, &destlen, (Bytef*)source, dataLen - sizeof(*header) );

    if( ret != Z_OK )
    {
        free( *out );
        *out = NULL;
        return -1;
    }

    return len;
}

bool ZipUtils::ccDeflateCCZFile(const char *filename, unsigned char *data, unsigned long dataLen)
{
    if ((filename == NULL) || (strlen(filename) < 1) || (data == NULL) || (dataLen < 1)) return false;
    uLongf destLen = dataLen * sizeof(unsigned char);
    Bytef *dest = new Bytef [destLen];
    memset(dest, 0, destLen);
    bool result = (compress(dest, &destLen, (Bytef*)data, dataLen) == Z_OK);
    if (result == false)
    {
        delete [] dest;
        return false;
    }

    struct CCZHeader header;
    header.sig[0] = 'C';
    header.sig[1] = 'C';
    header.sig[2] = 'Z';
    header.sig[3] = '!';

    header.version = CC_SWAP_INT16_BIG_TO_HOST(1);
    header.compression_type = CC_SWAP_INT16_BIG_TO_HOST(CCZ_COMPRESSION_ZLIB);
    header.len = CC_SWAP_INT32_BIG_TO_HOST((unsigned int) dataLen);

    FILE * fp = fopen(filename, "wb");
    result = false;
    if (fp)
    {
        fwrite(&header, 1, sizeof(CCZHeader), fp);
        fwrite(dest, 1, destLen, fp);
        fclose(fp);
        result = true;
    }

    delete [] dest;

    return result;
}
