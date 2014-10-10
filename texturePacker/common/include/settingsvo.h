#ifndef SETTINGSVO_H
#define SETTINGSVO_H

#include <QString>
#include <QObject>

class SettingsVO
{
public:
    enum format
    {
        IOS = 0,
        ANDROID = 1,
    };
public:
    SettingsVO();
    SettingsVO(const SettingsVO & svo);
    ~SettingsVO();
    bool operator ==(const SettingsVO & svo) const;
    const SettingsVO &operator =(const SettingsVO & svo);

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
