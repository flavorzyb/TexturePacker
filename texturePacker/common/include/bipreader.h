#ifndef BIPREADER_H
#define BIPREADER_H

#include "include/bipabstract.h"

class BipReader : public BipAbstract
{
    Q_OBJECT
public:
    explicit BipReader();
    virtual ~BipReader();
    bool load();
};

#endif // BIPREADER_H
