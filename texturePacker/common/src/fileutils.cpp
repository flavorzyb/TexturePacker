#include <QDir>
#include <QString>
#include "include/fileutils.h"

FileUtils::FileUtils() :
    QObject(NULL)
{
}

std::vector<std::string> FileUtils::getAllImageFiles(const std::string & path)
{
    std::vector<std::string> result;
    return result;
}

static std::string getParentPath(const std::string & path)
{
    QDir dir(path.c_str());
    std::string absPath = dir.absolutePath().toStdString();
    std::string dirname = dir.dirName().toStdString();
    if (absPath.length() > (dirname.length() + 1))
    {
        return absPath.substr(0, absPath.length() - dirname.length() - 1);
    }

    return "";
}

bool FileUtils::hasParentDirectory(const std::string & path)
{
    std::string parentPath = getParentPath(path);

    if (parentPath.length() > 0)
    {
        QDir parentDir(parentPath.c_str());
        return parentDir.exists();
    }

    return false;
}

bool FileUtils::createParentDirectory(const std::string & path)
{
    std::string parentPath = getParentPath(path);
    QDir parentDir(parentPath.c_str());
    return parentDir.mkpath(parentDir.absolutePath());
}
