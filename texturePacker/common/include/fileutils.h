#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QVector>
#include <QString>

class FileUtils : public QObject
{
    Q_OBJECT
public:
    FileUtils();
    static QVector<QString> getAllImageFiles(const QString & path);
    static bool hasParentDirectory(const QString & path);
    static bool createParentDirectory(const QString & path);
signals:

public slots:
};

#endif // FILEUTILS_H
