#ifndef IOUTILS_H
#define IOUTILS_H

#include <QObject>

class IOUtils : public QObject
{
    Q_OBJECT
public:
    static const bool IS_BIG_ENDIAN;
    static void readOrderData(unsigned char *pData, unsigned int len);
    static void writeOrderData(unsigned char *pData, unsigned int len);
};

#endif // IOUTILS_H
