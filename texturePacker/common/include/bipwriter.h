#ifndef BIPWRITER_H
#define BIPWRITER_H

#include <QObject>
#include <QString>

#include "include/bipabstract.h"
#include "include/writer.h"

class BipWriter : public BipAbstract
{
public:
    explicit BipWriter(BipImage *img);
    virtual ~BipWriter();
    bool save(const QString & filepath);

private:
    void initWriter(Writer * writer);
    bool writerHeadData(Writer * writer, const QString & filepath);
    bool writerData(const QString & filepath);
};

#endif // BIPWRITER_H
