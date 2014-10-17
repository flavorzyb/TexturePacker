#include "include/settingsvo.h"
#include "include/fileutils.h"

SettingsVO::SettingsVO():
    m_inputPath("")
  , m_outputPath("")
  , m_format(SettingsVO::IOS)
  , m_minSize(0)
  , m_excludePathMap()
{
}

SettingsVO::SettingsVO(const SettingsVO & svo):
    m_inputPath(svo.m_inputPath)
  , m_outputPath(svo.m_outputPath)
  , m_format(svo.m_format)
  , m_minSize(svo.m_minSize)
  , m_excludePathMap(svo.m_excludePathMap)
{
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

QString SettingsVO::getAbsoluteInputDirPath() const
{
    return FileUtils::getAbsoluteDirPath(m_inputPath);
}

QString SettingsVO::getInputPath() const
{
    return m_inputPath;
}

QString SettingsVO::getOutputPath() const
{
    return m_outputPath;
}

QString SettingsVO::getAbsoluteOutputDirPath() const
{
    return FileUtils::getAbsoluteDirPath(m_outputPath);
}

SettingsVO::format SettingsVO::getFormat() const
{
    return m_format;
}

void SettingsVO::addExcludePath(const QString &path)
{
    if (path.length() > 0)
    {
        QString absPath = FileUtils::getAbsoluteDirPath(path);
        if (!m_excludePathMap.contains(absPath))
        {
            m_excludePathMap.insert(absPath, true);
        }
    }
}

bool SettingsVO::isInExcludePath(const QString &path) const
{
    if (m_excludePathMap.size() > 0)
    {
        QHash<QString, bool>::const_iterator iterator = m_excludePathMap.begin();
        for (; iterator != m_excludePathMap.end(); iterator++)
        {
            if (path.startsWith(iterator.key()))
            {
                return true;
            }
        }
    }

    return false;
}
unsigned int SettingsVO::minSize() const
{
    return m_minSize;
}

void SettingsVO::setMinSize(unsigned int minSize)
{
    m_minSize = minSize;
}


bool SettingsVO::operator ==(const SettingsVO & svo) const
{
    return ((m_inputPath == svo.m_inputPath) &&
            (m_outputPath == svo.m_outputPath) &&
            (m_format == svo.m_format) &&
            (m_minSize == svo.m_minSize)
            (m_excludePathMap == svo.m_excludePathMap));
}

const SettingsVO & SettingsVO::operator =(const SettingsVO &svo)
{
    m_inputPath         = svo.m_inputPath;
    m_outputPath        = svo.m_outputPath;
    m_format            = svo.m_format;
    m_minSize           = svo.m_minSize;
    m_excludePathMap    = svo.m_excludePathMap;

    return (*this);
}
