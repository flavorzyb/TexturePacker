#include "include/bipwriter.h"

BipWriter::BipWriter(PVR *pvr):BipAbstract()
{
    setPvr(pvr);
}

BipWriter::~BipWriter()
{
}

bool BipWriter::save(const QString &filepath)
{
    return false;
}
