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
    enum{HEAD_DATA_SIZE = 8};

    PVR *pvr() const;
    void setPvr(PVR *pvr);

private:
    BipAbstract(const BipAbstract & BipAbstract);
    const BipAbstract & operator = (const BipAbstract & bip);
    static const unsigned char BIP_HEAD_DATA[HEAD_DATA_SIZE];
private:
    PVR *m_pvr;
};

#endif // BIPABSTRACT_H
