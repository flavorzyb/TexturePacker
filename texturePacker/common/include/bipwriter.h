#ifndef BIPWRITER_H
#define BIPWRITER_H

#include <QObject>
#include <QString>

#include "include/pvr.h"

class BipWriter : public QObject
{
    Q_OBJECT
public:
    explicit BipWriter(PVR *pvr);

    bool save(const QString & filepath);

private:
    PVR *m_pvr;
};

#endif // BIPWRITER_H
