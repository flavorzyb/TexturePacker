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
    const Png2BipCahceVO *getCacheVO(const QString & key, const QString & md5String) const;
    inline unsigned int size() const {return m_map.size();}
    inline QString getVersion() const {return m_version;}
private:
    QMap<QString, Png2BipCahceVO> m_map;
    QString m_version;
};

#endif // PNG2BIPCACHELOADER_H
