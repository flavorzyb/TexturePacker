#include "include/settingsvo.h"

SettingsVO::SettingsVO():m_inputPath("")
                        ,m_outputPath("")
                        ,m_format(SettingsVO::IOS)
{
}

SettingsVO::SettingsVO(const SettingsVO & svo)
{
    m_inputPath = svo.m_inputPath;
    m_outputPath = svo.m_outputPath;
    m_format = svo.m_format;
}

SettingsVO::~SettingsVO()
{

}

void SettingsVO::setInputPath(QString path)
{
    m_inputPath = path;
}

void SettingsVO::setOutputPath(QString path)
{
    m_outputPath = path;
}

void SettingsVO::setFormat(SettingsVO::format f)
{
    m_format = f;
}

const QString & SettingsVO::getInputPath() const
{
    return m_inputPath;
}

const QString & SettingsVO::getOutputPath() const
{
    return m_outputPath;
}

SettingsVO::format SettingsVO::getFormat() const
{
    return m_format;
}

bool SettingsVO::operator ==(const SettingsVO & svo) const
{
    return ((m_inputPath == svo.getInputPath()) &&
            (m_outputPath == svo.getOutputPath()) &&
            (m_format == svo.getFormat()));
}
