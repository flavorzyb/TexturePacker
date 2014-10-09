#include "include/bipabstract.h"

const unsigned char BipAbstract::BIP_HEAD_DATA[BipAbstract::HEAD_DATA_SIZE] = {0x89, 'B', 'I', 'P', 0x0D, 0x0A, 0x1A, 0x0A};

BipAbstract::BipAbstract():m_pvr(NULL)
{
}

BipAbstract::~BipAbstract()
{
    if (NULL != m_pvr)
    {
        delete m_pvr;
    }
}

PVR *BipAbstract::pvr() const
{
    return m_pvr;
}

void BipAbstract::setPvr(PVR *pvr)
{
    m_pvr = pvr;
}

bool BipAbstract::isBipFile(const unsigned char *buffer, unsigned long size)
{
    if (size <= HEAD_DATA_SIZE)
    {
        return false;
    }

    return (0 == memcmp(BIP_HEAD_DATA, buffer, HEAD_DATA_SIZE));
}

