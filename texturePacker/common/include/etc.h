#ifndef ETC_H
#define ETC_H

#include <QString>
#include "include/image.h"

class ETC : public Image
{
public:
    explicit ETC();
    explicit ETC(const QString & filename);

};

#endif // ETC_H
