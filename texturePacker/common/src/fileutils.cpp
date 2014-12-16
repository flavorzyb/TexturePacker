#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QFile>
#include <iostream>
#include <QByteArray>
#include <QCryptographicHash>
#include <QThread>
#include "include/fileutils.h"
#include "include/config.h"

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

QVector<QString> FileUtils::getAllFiles(const QString &path)
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
                result += getAllFiles(iterator->absoluteFilePath());
            }
            else if (iterator->isFile())
            {
                result.push_back(iterator->absoluteFilePath());
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

QString FileUtils::getAbsoluteFilePath(const QString &path)
{
    QFileInfo fileInfo(path);
    return fileInfo.absoluteFilePath();
}

QString FileUtils::getAbsoluteDirPath(const QString &path)
{
    QDir dir(path);

    return dir.absolutePath();
}

unsigned char* FileUtils::getFileData(const QString & pszFileName, const char* pszMode, unsigned long * pSize)
{
    return getFileData(pszFileName.toStdString().c_str(), pszMode, pSize);
}

unsigned char *FileUtils::getFileData(const char *pszFileName, const char *pszMode, unsigned long *pSize)
{
    unsigned char * pBuffer = NULL;
    *pSize = 0;

    if (pszFileName == NULL || pSize == NULL || pszMode == NULL)
    {
        return NULL;
    }

    // read the file from hardware
    FILE *fp = fopen(pszFileName, pszMode);

    if (!fp)
    {
        return NULL;
    }

    fseek(fp,0,SEEK_END);
    *pSize = ftell(fp);
    fseek(fp,0,SEEK_SET);
    pBuffer = new unsigned char[*pSize];
    *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
    fclose(fp);

    return pBuffer;
}

#define WRITE_FILE_DATA(filename, mode, contentType, content, size) \
    if (!(fileName && mode && content)) \
    { \
        return false; \
    } \
    \
    FILE * fp = fopen(fileName, mode); \
    if (fp) \
    { \
        fwrite(content, sizeof(contentType), size, fp); \
        fclose(fp); \
    \
        return true; \
    } \

bool FileUtils::writeFile(const QString & fileName,
                          const char * mode,
                          const unsigned char * content,
                          unsigned long size)
{
    return writeFile(fileName.toStdString().c_str(), mode, content, size);
}

bool FileUtils::writeFile(const char *fileName, const char *mode, const unsigned char *content, unsigned long size)
{
    WRITE_FILE_DATA(filename, mode, unsigned char, content, size)

    return false;
}
bool FileUtils::writeFile(const QString & fileName,
                      const char * mode,
                      const char * content,
                      unsigned long size)
{
    return writeFile(fileName.toStdString().c_str(), mode, content, size);
}

bool FileUtils::writeFile(const char *fileName, const char *mode, const char *content, unsigned long size)
{
    WRITE_FILE_DATA(fileName, mode, char, content, size)

    return false;
}

#undef WRITE_FILE_DATA
QString FileUtils::createImageTempFolder()
{
    QString path = QDir::homePath() + "/.tp/tmp";
    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(path);
    }

    return path;
}

QString FileUtils::getRandFileNameString()
{
    qsrand(time(0));
    int t1 = qrand();
    int t2 = qrand();
    char strFile[32] = {0};
    sprintf(strFile, "%d_%d", t1, t2);
    return strFile;
}

bool FileUtils::unlink(const QString &filename)
{
    QFile file(filename);
    if (file.exists())
    {
        return file.remove();
    }

    return true;
}

QString FileUtils::md5(const QString &str)
{
    QCryptographicHash cryto(QCryptographicHash::Md5);
    cryto.addData(str.toStdString().c_str(), str.toStdString().length());
    QString result(cryto.result().toHex());
    return result;
}

bool FileUtils::isDir(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return (fileInfo.exists() && fileInfo.isDir());
}

bool FileUtils::isFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return (fileInfo.exists() && fileInfo.isFile());
}

QString FileUtils::md5File(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QCryptographicHash cryto(QCryptographicHash::Md5);
    cryto.addData(&file);
    QString result(cryto.result().toHex());
    file.close();

    return result;
}

QString FileUtils::getPng2BipCacheDirPath(const QString &hashPath, SettingsVO::format format)
{
    char strFormat[32] = {0};
    snprintf(strFormat, sizeof(strFormat), "%d", format);
    QString path = QDir::homePath() + "/.tp/cache/" + md5(hashPath + strFormat);
    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(path);
    }

    return path;
}

QString FileUtils::getPng2BipCacheFilePath(const QString &hashPath, SettingsVO::format format)
{
    return (getPng2BipCacheDirPath(hashPath, format) + "/png2bip_" + Config::VERSION + ".cache");
}

bool FileUtils::copyFile(const QString &sourceFileName, const QString &destFileName)
{
    FileUtils::createParentDirectory(destFileName);
    unlink(destFileName);

    return QFile::copy(sourceFileName, destFileName);
}

unsigned int FileUtils::getFileSize(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.size();
}

QString FileUtils::getFileBaseName(const QString & filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.completeBaseName();
}
