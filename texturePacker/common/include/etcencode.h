#ifndef ETCENCODE_H
#define ETCENCODE_H
#include <QString>
#include "include/etc.h"

class ETCEncode
{
public:
    ETCEncode();
    virtual ~ETCEncode();
    ETC * convert(const QString & pngPath);
private:
    ETCEncode(const ETCEncode & etc);
    ETCEncode & operator = (const ETCEncode & etc);
};

#endif // ETCENCODE_H
