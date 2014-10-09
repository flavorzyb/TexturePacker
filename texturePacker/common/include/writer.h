#ifndef WRITER_H
#define WRITER_H

#include <QString>
#include <QObject>

class Writer : public QObject
{
    Q_OBJECT
public:
    explicit Writer(unsigned  int size = 4096);
    ~Writer();
    bool writeInt(int value);
    bool writeUnsignedInt(unsigned int value);
    bool writeShort(short value);
    bool writeString(const QString & value);
    bool writeByte(unsigned char value);
    bool writeBoolean(bool value);
    bool writeFloat(float value);
    bool copyBytes(const unsigned char * value, unsigned int len);
    unsigned char * getData() const;
    unsigned int getLenght() const;
private:
    unsigned char * m_buffer;
    unsigned int m_size;
    unsigned int m_offset;
};

#endif // WRITER_H
