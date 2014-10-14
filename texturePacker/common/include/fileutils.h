#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QVector>
#include <QString>

#include "include/settingsvo.h"

class FileUtils : public QObject
{
    Q_OBJECT
public:
    FileUtils();
    static QVector<QString> getAllImageFiles(const QString & path);
    static QVector<QString> getAllFiles(const QString & path);
    static bool hasParentDirectory(const QString & path);
    static bool createParentDirectory(const QString & path);
    static QString getAbsoluteFilePath(const QString & path);
    static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    static bool writeFile(const char * fileName, const char * mode, const unsigned char * content, unsigned long size);
    static bool writeFile(const char * fileName, const char * mode, const char * content, unsigned long size);
    static QString createImageTempFolder();
    static QString getRandFileNameString();
    static bool unlink(const QString & filename);
    static QString md5(const QString & str);
    static bool isDir(const QString & filePath);
    static QString md5File(const QString & filePath);
    static QString getPng2BipCacheDirPath(const QString &hashPath, SettingsVO::format format);
    static QString getPng2BipCacheFilePath(const QString &hashPath, SettingsVO::format format);
signals:

public slots:
};

#endif // FILEUTILS_H
