#include "include/pvr.h"

PVR::PVR():Image()
{
}

PVR::PVR(QString filename):Image(filename)
{
}

PVR::PVR(const PVR &pvr):Image(pvr)
{
}

bool PVR::load()
{
    return true;
}
