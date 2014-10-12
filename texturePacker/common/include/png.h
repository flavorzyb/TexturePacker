#ifndef PNG_H
#define PNG_H
#include "include/image.h"

class PVR;

class PNG : public Image
{
    Q_OBJECT
public:
    PNG();
    PNG(const QString & filename);
    virtual ~PNG();
    virtual bool load();
    bool loadData(const unsigned char * pData, int width, int height);
    PVR * convertToPVR();
    virtual bool save(const QString & filename);
    inline const QImage * getImage() const {return m_pImg;}
private:
    int findFirstHorizontalNoBlank();
    int findLastHorizontalNoBlank();
    int findFirstVerticalNoBlank();
    int findLastVerticalNoBlank();
    unsigned char * createImageData(int fnw,  int fnh, int w, int h, int pw, int ph, int windex, int hindex);

private:
    QImage * m_pImg;
};

#endif // PNG_H
