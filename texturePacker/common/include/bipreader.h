#ifndef BIPREADER_H
#define BIPREADER_H

#include <QString>
#include "include/pvr.h"
#include "include/bipabstract.h"

class BipReader : public BipAbstract
{
    Q_OBJECT
public:
    explicit BipReader(const QString & fileName);
    virtual ~BipReader();
    PVR * load();
    PVR * load(const QString & fileName);
    QString fileName() const;

private:
    void setFileName(const QString &fileName);
private:
    QString m_fileName;
};

#endif // BIPREADER_H
