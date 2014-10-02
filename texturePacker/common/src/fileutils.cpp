#include <QDir>
#include <QFileInfo>
#include <QStringList>

#include "include/fileutils.h"

FileUtils::FileUtils() :
    QObject(NULL)
{
}

QVector<QString> FileUtils::getAllImageFiles(const QString & path)
{
    QVector<QString> result;
    QDir dir(path);
    QFileInfoList fileInfoLists = dir.entryInfoList();
    QFileInfoList::const_iterator iterator = fileInfoLists.constBegin();

    for(; iterator != fileInfoLists.constEnd(); iterator++)
    {
        QString filename = iterator->fileName();

        if (!filename.startsWith("."))
        {
            if (iterator->isDir())
            {
                result += getAllImageFiles(iterator->absoluteFilePath());
            }
            else if (iterator->isFile())
            {
                QString ext = iterator->completeSuffix();
                QString extLower = ext.toLower();
                if (extLower.endsWith("png") ||
                        extLower.endsWith("jpg") ||
                        extLower.endsWith("jpeg"))
                {
                    result.push_back(iterator->absoluteFilePath());
                }
            }
            else
            {
                //
            }
        }
    }

    return result;
}

static QString getParentPath(const QString & path)
{
    QFileInfo fileInfo(path);

    return fileInfo.absolutePath();
}

bool FileUtils::hasParentDirectory(const QString & path)
{
    QString parentPath = getParentPath(path);

    if (parentPath.length() > 0)
    {
        QDir parentDir(parentPath);
        return parentDir.exists();
    }

    return false;
}

bool FileUtils::createParentDirectory(const QString & path)
{
    QString parentPath = getParentPath(path);
    QDir parentDir;
    return parentDir.mkpath(parentPath);
}
