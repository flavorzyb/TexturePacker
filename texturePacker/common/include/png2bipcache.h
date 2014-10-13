#ifndef PNG2BIPCACHE_H
#define PNG2BIPCACHE_H
#include <QMap>
#include <QString>

#include "include/png2bipcahcevo.h"

class Png2BipCache
{
public:
    Png2BipCache();
    bool load(const QString & path);
    bool save(const QString & path);
    void add(const Png2BipCahceVO & value);
    const Png2BipCahceVO *getCacheVO(const QString & key) const;
    inline unsigned int size() const {return m_map.size();}
private:
    QMap<QString, Png2BipCahceVO> m_map;
};

#endif // PNG2BIPCACHELOADER_H
