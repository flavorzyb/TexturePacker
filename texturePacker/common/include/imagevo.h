#ifndef IMAGEVO_H
#define IMAGEVO_H

#include <QString>
#include <QSize>
#include <QRect>
#include <QPoint>
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
    void setSourceSize(int width, int height);

    QPoint offset() const;
    void setOffset(const QPoint &offset);
    void setOffset(int x, int y);

    QRect rect() const;
    void setRect(const QRect &rect);
    void setRect(int x, int y, int width, int height);

    bool rotated() const;
    void setRotated(bool rotated);

    QString fileName() const;
    void setFileName(const QString &fileName);

    const ImageVO & operator=(const ImageVO & ivo);
    QRect sourceColorRect() const;
    void setSourceColorRect(const QRect &sourceColorRect);
    void setSourceColorRect(int x, int y, int width, int height);

    QSize size() const;
    void setSize(const QSize &size);
    void setSize(int width, int height);

private:
    QSize m_sourceSize;
    QPoint m_offset;
    QRect m_rect;
    bool m_rotated;
    QString m_fileName;
    QRect m_sourceColorRect;
    QSize m_size;
};

#endif // IMAGEVO_H
