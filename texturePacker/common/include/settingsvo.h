#ifndef SETTINGSVO_H
#define SETTINGSVO_H

#include <QString>
#include <QObject>
#include <QHash>

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
    const SettingsVO & operator =(const SettingsVO & svo);

    void setInputPath(QString path);
    void setOutputPath(QString path);
    void setFormat(format f);

    inline bool isIOSFormat() const { return m_format == IOS;}
    inline bool isAndroidFormat() const { return m_format == ANDROID;}

    QString getInputPath() const;
    QString getAbsoluteInputDirPath() const;
    QString getOutputPath() const;
    QString getAbsoluteOutputDirPath() const;

    format getFormat() const;

    void addExcludePath(const QString & path);
    bool isInExcludePath(const QString & path) const;
    unsigned int minSize() const;
    void setMinSize(unsigned int minSize);

private:
    QString                 m_inputPath;
    QString                 m_outputPath;
    format                  m_format;
    unsigned int            m_minSize;
    QHash<QString, bool>    m_excludePathMap;
};

#endif // SETTINGSVO_H
