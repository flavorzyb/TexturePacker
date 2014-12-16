#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QString>
#include <QImage>

class Image
{
public:
    Image();
    Image(const QString & filename);
    //Image(const Image & img);
    virtual ~Image();

    bool loadFile(const QString & filename);
    virtual bool load() = 0;
    virtual bool save(const QString & filename) = 0;
    int width() const;
    int height() const;
    const QString & filePath() const;
    bool exists(const QString & filename) const;

protected:
    void setFilePath(const QString &filePath);
    void setWidth(int width);
    void setHeight(int height);

private:
    QString m_filePath;
    int m_width;
    int m_height;
};

#endif // IMAGE_H
