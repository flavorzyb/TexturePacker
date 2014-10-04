#ifndef PVRABSTRACT_H
#define PVRABSTRACT_H

#include <QObject>
#include <QString>

class PVRAbstract : public QObject
{
    Q_OBJECT
public:
    PVRAbstract();
    bool load(QString filename);

    virtual bool load() = 0;

    int width() const;
    int height() const;
    const QString & filePath() const;
signals:

public slots:

private:
    void setFilePath(const QString &filePath);
    void setWidth(int width);
    void setHeight(int height);

private:
    QString m_filePath;
    int m_width;
    int m_height;
};

#endif // PVRABSTRACT_H
