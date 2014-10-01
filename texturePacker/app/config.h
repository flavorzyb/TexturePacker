#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QObject>


class Config : public QObject
{
public:
    static const QString AUTHOR;
    static const QString VERSION;
    static const QString DATE;
};

#endif // CONFIG_H
