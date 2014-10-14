#ifndef PNG2BIPCAHCE_H
#define PNG2BIPCAHCE_H
#include <QString>

class Png2BipCahceVO
{
public:
    Png2BipCahceVO();

    QString pngFilePath() const;
    void setPngFilePath(const QString &pngFilePath);

    QString pngFileMd5String() const;
    void setPngFileMd5String(const QString &pngFileMd5String);

    QString bipFilePath() const;
    void setBipFilePath(const QString &bipFilePath);

    QString bipFileMd5String() const;
    void setBipFileMd5String(const QString &bipFileMd5String);

private:
    QString m_pngFilePath;
    QString m_pngFileMd5String;
    QString m_bipFilePath;
    QString m_bipFileMd5String;
};

#endif // PNG2BIPCAHCE_H
