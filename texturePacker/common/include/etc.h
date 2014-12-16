#ifndef ETC_H
#define ETC_H

#include <QString>
#include "include/image.h"
#include "include/imagevo.h"

class ETC : public Image
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

    const ImageVO imagevo() const;
    void setImagevo(const ImageVO & imagevo);
    inline const unsigned char * getData() const {return m_data;}
    inline unsigned long getSize() const {return m_size;}

private:
    ETC(const ETC & etc);
    bool loadETC(const QString & filename);

private:
    ImageVO m_imagevo;
    unsigned char * m_data;
    unsigned long m_size;
};

#endif // ETC_H
