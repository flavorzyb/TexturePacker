#include "include/writer.h"
#include "include/ioutils.h"

Writer::Writer(int size):
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

#define CMDWRITER_SYNTHESIZE(varType, functionName) \
    bool Writer::write##functionName(varType value) \
    { \
        int len = sizeof(varType); \
        memcpy(m_buffer, &value, len);\
        \
        IOUtils::orderData(m_buffer + m_offset, len);\
        \
        m_offset +=len;\
        return true; \
    }

    CMDWRITER_SYNTHESIZE(int, Int)
    CMDWRITER_SYNTHESIZE(unsigned int, UnsignedInt)
    CMDWRITER_SYNTHESIZE(short, Short)
    CMDWRITER_SYNTHESIZE(unsigned char, Byte)
    CMDWRITER_SYNTHESIZE(bool, Boolean)
    CMDWRITER_SYNTHESIZE(float, Float)
#undef CMDWRITER_SYNTHESIZE

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

unsigned char *Writer::getData() const
{
    return m_buffer;
}

int Writer::getLenght() const
{
    return m_offset;
}
