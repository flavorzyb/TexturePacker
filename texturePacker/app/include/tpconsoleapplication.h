#ifndef TPCONSOLEAPPLICATION_H
#define TPCONSOLEAPPLICATION_H

#include <QCoreApplication>

#include "common/include/settingsvo.h"
#include "common/include/publisher.h"

class ConsolePubThread : public QThread
{
public:
    ConsolePubThread(const SettingsVO & svo);
    virtual ~ConsolePubThread();
private:
    void run();

private:
    Publisher * m_pub;
};

class TPConsoleApplication : public QCoreApplication
{
    Q_OBJECT
public:
    explicit TPConsoleApplication(int &argc, char **argv);
    virtual ~TPConsoleApplication();
    bool checkConsole();
    inline bool isInitCache() const {return m_isInitCache;}
    bool initCache();
    void runConsole();
private:
    bool initCache(const SettingsVO & svo, const QString & initCachePath);
    void print_usage();

private:
    int m_args;
    SettingsVO m_svo;
    bool m_isInitCache;
    QString m_initCachePath;
    ConsolePubThread * m_pub;
};

#endif // TPCONSOLEAPPLICATION_H
