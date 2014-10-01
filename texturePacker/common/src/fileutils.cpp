#include "include/fileutils.h"

FileUtils::FileUtils() :
    QObject(NULL)
{
}

std::vector<std::string> FileUtils::getAllImageFiles(const std::string & path)
{

}

bool FileUtils::hasParentDirectory(const std::string & path)
{
    return true;
}

bool FileUtils::createParentDirectory(const std::string & path)
{
    return true;
}
