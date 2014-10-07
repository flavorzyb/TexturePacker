#ifndef IMAGEVO_H
#define IMAGEVO_H

#include <QString>
#include <QSize>
#include <QRect>
#include <QObject>

class ImageVO : public QObject
{
    Q_OBJECT
public:
    explicit ImageVO(const QSize & size);
    explicit ImageVO(int w, int h);
    ImageVO(const ImageVO & ivo);

    QSize sourceSize() const;
    void setSourceSize(const QSize &sourceSize);

    QSize offset() const;
    void setOffset(const QSize &offset);

    QRect rect() const;
    void setRect(const QRect &rect);

    bool rotated() const;
    void setRotated(bool rotated);

    QString fileName() const;
    void setFileName(const QString &fileName);

private:
    QSize m_sourceSize;
    QSize m_offset;
    QRect m_rect;
    bool m_rotated;
    QString m_fileName;
};

#endif // IMAGEVO_H
