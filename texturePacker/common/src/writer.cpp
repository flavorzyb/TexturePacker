#include "include/writer.h"
#include "include/ioutils.h"

Writer::Writer(unsigned int size):
    m_buffer(NULL)
  , m_size(size)
  , m_offset(0)
{
    if (size > 0)
    {
        m_buffer = new unsigned char [size + 1];
        memset(m_buffer, 0, (size + 1) * sizeof(unsigned char));
    }
}

Writer::~Writer()
{
    if (NULL != m_buffer)
    {
        delete [] m_buffer;
    }
}

#define WRITER_SYNTHESIZE(varType, functionName) \
    bool Writer::write##functionName(varType value) \
    { \
        int len = sizeof(varType); \
        memcpy(m_buffer+ m_offset, &value, len);\
        \
        IOUtils::orderData(m_buffer + m_offset, len);\
        \
        m_offset +=len;\
        return true; \
    }

    WRITER_SYNTHESIZE(int, Int)
    WRITER_SYNTHESIZE(unsigned int, UnsignedInt)
    WRITER_SYNTHESIZE(short, Short)
    WRITER_SYNTHESIZE(unsigned char, Byte)
    WRITER_SYNTHESIZE(bool, Boolean)
    WRITER_SYNTHESIZE(float, Float)
#undef WRITER_SYNTHESIZE

bool Writer::writeString(const QString &value)
{
    int len = value.length();
    if (len > 0)
    {
        writeShort(len);
        memcpy(m_buffer + m_offset, value.toStdString().c_str(), len);
        m_offset += len;
    }

    return true;
}

bool Writer::copyBytes(const unsigned char * value, unsigned int len)
{
    if ((NULL != value) && (len > 0))
    {
        memcpy(m_buffer + m_offset, value, len * sizeof(unsigned char));
        m_offset += len;
        return true;
    }

    return false;
}

unsigned char *Writer::getData() const
{
    return m_buffer;
}

unsigned int Writer::getLenght() const
{
    return m_offset;
}
