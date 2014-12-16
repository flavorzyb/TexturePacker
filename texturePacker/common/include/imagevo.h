#ifndef IMAGEVO_H
#define IMAGEVO_H

#include <QVector>
#include "include/framevo.h"

class ImageVO
{
public:
    explicit ImageVO(const QSize & size);
    explicit ImageVO(int w, int h);
    ImageVO(const ImageVO & ivo);
    const ImageVO & operator= (const ImageVO & ivo);

    QSize size() const;
    void setSize(const QSize &size);
    void setSize(int width, int height);

    QString fileName() const;
    void setFileName(const QString &fileName);

    const QVector<FrameVO> & frames() const;
    void setFrames(const QVector<FrameVO> &frames);
    void addFrame(const FrameVO & fvo);
    void chopFrameNamePath(const QString & path);
    inline unsigned int getFramesCount() const {return m_frames.size();}
private:
    QString m_fileName;
    QSize m_size;
    QVector<FrameVO> m_frames;
};

#endif // FrameVO_H
