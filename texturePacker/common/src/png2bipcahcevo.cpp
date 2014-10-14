#include "include/png2bipcahcevo.h"

Png2BipCahceVO::Png2BipCahceVO()
{
}

QString Png2BipCahceVO::pngFilePath() const
{
    return m_pngFilePath;
}

void Png2BipCahceVO::setPngFilePath(const QString &pngFilePath)
{
    m_pngFilePath = pngFilePath;
}

QString Png2BipCahceVO::pngFileMd5String() const
{
    return m_pngFileMd5String;
}

void Png2BipCahceVO::setPngFileMd5String(const QString &pngFileMd5String)
{
    m_pngFileMd5String = pngFileMd5String;
}

QString Png2BipCahceVO::bipFilePath() const
{
    return m_bipFilePath;
}

void Png2BipCahceVO::setBipFilePath(const QString &bipFilePath)
{
    m_bipFilePath = bipFilePath;
}

QString Png2BipCahceVO::bipFileMd5String() const
{
    return m_bipFileMd5String;
}

void Png2BipCahceVO::setBipFileMd5String(const QString &bipFileMd5String)
{
    m_bipFileMd5String = bipFileMd5String;
}
