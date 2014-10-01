#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <vector>
#include <string>

class FileUtils : public QObject
{
    Q_OBJECT
public:
    FileUtils();
    static std::vector<std::string> getAllImageFiles(const std::string & path);
    static bool hasParentDirectory(const std::string & path);
    static bool createParentDirectory(const std::string & path);
signals:

public slots:

};

#endif // FILEUTILS_H
