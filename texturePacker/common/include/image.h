#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QString>
#include <QImage>

class Image : public QObject
{
    Q_OBJECT
public:
    Image();
    Image(QString filename);
    Image(const Image & img);

    bool load(QString filename);
    virtual bool load() = 0;
    int width() const;
    int height() const;
    const QString & filePath() const;

signals:

public slots:

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
