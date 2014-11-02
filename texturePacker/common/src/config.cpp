#include "../include/config.h"

const QString Config::AUTHOR = tr("朱彦斌");
const QString Config::DATE = tr("2014-11-2");
const QString Config::VERSION = tr("1.1.0");

bool Config::m_isConsole = false;

bool Config::isConsole()
{
    return m_isConsole;
}

void Config::setIsConsole(bool isConsole)
{
    m_isConsole = isConsole;
}
