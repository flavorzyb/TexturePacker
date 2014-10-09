#ifndef BIPWRITER_H
#define BIPWRITER_H

#include <QObject>
#include <QString>

#include "include/bipabstract.h"

class BipWriter : public BipAbstract
{
    Q_OBJECT
public:
    explicit BipWriter(PVR *pvr);
    virtual ~BipWriter();
    bool save(const QString & filepath);
};

#endif // BIPWRITER_H
