#ifndef READER_H
#define READER_H

#include <QObject>
#include <QString>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(unsigned char *pData, unsigned long nSize);
    virtual ~Reader();

    unsigned char readByte();
    bool readBoolean();
    unsigned int readUnsignedInt();
    int readInt();
    float readFloat();
    QString readString();
    short readShort();
    void skip(int offset);
    bool isUTF8BOM();
    void skipUTF8BOM();
    inline unsigned long getOffset() const { return m_offset;}
    inline unsigned char * getData()const {return (m_pData+m_offset);}
    inline unsigned long getSize()const {return (m_nSize - m_offset);}
private:
    unsigned char * m_pData;
    unsigned long m_nSize;
    unsigned long m_offset;
    Reader(const Reader & reader);
    const Reader & operator=(const Reader &reader);
};

#endif // READER_H
