#ifndef ETC_H
#define ETC_H

#include <QString>
#include "include/bipimage.h"

class ETC : public BipImage
{
public:
    ETC();
    explicit ETC(const QString & filename);
    virtual ~ETC();

    virtual bool load();
    bool loadData(const unsigned char * pData, unsigned long size);
    bool loadCCZData(const unsigned char * pData, unsigned long size);
    virtual bool save(const QString & filename);
    bool saveCCZ(const QString & filename);
    unsigned char * saveCCZToBuffer(unsigned long *size);

    inline const unsigned char * getData() const {return m_data;}
    inline unsigned long getSize() const {return m_size;}

private:
    ETC(const ETC & etc);
    bool loadETC(const QString & filename);

private:
    unsigned char * m_data;
    unsigned long m_size;
};

#endif // ETC_H
