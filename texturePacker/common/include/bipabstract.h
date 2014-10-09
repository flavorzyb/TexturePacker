#ifndef BIPABSTRACT_H
#define BIPABSTRACT_H

#include <QObject>

#include "include/pvr.h"

class BipAbstract : public QObject
{
    Q_OBJECT
public:
    explicit BipAbstract();
    virtual ~BipAbstract();
    PVR * pvr() const;
    void setPvr(PVR *pvr);
    bool isBipFile(const unsigned char * buffer, unsigned long size);
public:
    enum{HEAD_DATA_SIZE = 8};
    static const unsigned char BIP_HEAD_DATA[HEAD_DATA_SIZE];

private:
    BipAbstract(const BipAbstract & BipAbstract);
    const BipAbstract & operator = (const BipAbstract & bip);

private:
    PVR *m_pvr;
};

#endif // BIPABSTRACT_H
