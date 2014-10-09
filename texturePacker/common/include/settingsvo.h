#ifndef SETTINGSVO_H
#define SETTINGSVO_H

#include <QString>
#include <QObject>

class SettingsVO : public QObject
{
public:
    enum format
    {
        IOS = 0,
        ANDROID = 1,
    };
    Q_OBJECT
public:
    SettingsVO();
    SettingsVO(const SettingsVO & svo);
    ~SettingsVO();
    bool operator ==(const SettingsVO & svo) const;
    void setInputPath(QString path);
    void setOutputPath(QString path);
    void setFormat(format f);

    QString getInputPath() const;
    QString getAbsoluteInputFilePath() const;
    QString getOutputPath() const;

    format getFormat() const;
private:
    QString m_inputPath;
    QString m_outputPath;
    format m_format;
};

#endif // SETTINGSVO_H
