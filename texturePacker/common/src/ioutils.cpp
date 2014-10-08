#include "include/ioutils.h"
#include "include/macros.h"

const bool IOUtils::IS_BIG_ENDIAN = CC_HOST_IS_BIG_ENDIAN;

void IOUtils::orderData(unsigned char *pData, unsigned int len)
{
    if (!IS_BIG_ENDIAN)
    {
        unsigned char *data = new unsigned char [len];
        for (unsigned int i = 0; i< len; i++)
        {
            *(data+i) = *(pData+len-i-1);
        }

        memcpy(pData, data, len);

        delete [] data;
    }
}
