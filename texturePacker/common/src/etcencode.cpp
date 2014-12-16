#include "include/etcencode.h"
#include "include/fileutils.h"

ETCEncode::ETCEncode()
{
}

ETCEncode::~ETCEncode()
{
}

ETC * ETCEncode::convert(const QString & pngPath)
{
    if (FileUtils::isFile(pngPath) == false)
    {
        return NULL;
    }



    return NULL;
}
