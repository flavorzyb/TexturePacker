#include "../include/config.h"

const QString Config::AUTHOR = tr("朱彦斌");
const QString Config::DATE = tr("2014-12-17");
const QString Config::VERSION = tr("1.2.0");

bool Config::m_isConsole = false;

bool Config::isConsole()
{
    return m_isConsole;
}

void Config::setIsConsole(bool isConsole)
{
    m_isConsole = isConsole;
}
