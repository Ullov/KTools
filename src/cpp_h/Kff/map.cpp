#include "map.h"
#include "pointer.h"
#include "list.h"
#include "string.h"

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(KTools::Kff::Manager *man) : KTools::Kff::String(man)
{
    keys = new List<K>(man);
    values = new List<V>(man);
    data = keys->pointer->getAll();
    data += values->pointer->getAll();
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(KTools::Kff::Manager *man, const qint64 pos) : KTools::Kff::String(man, pos)
{
    Pointer lPointer(man, data.mid(0, 9));
    keys = new List<K>(man, lPointer);
    lPointer.setAll(data.mid(9));
    values = new List<V>(man, lPointer);
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(Pointer *poi) : KTools::Kff::String(poi)
{
    keys = new List<K>(poi);
    values = new List<V>(poi);
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::~Map()
{
    delete keys;
    delete values;
}

template <typename K, typename V>
void KTools::Kff::Map<K, V>::append(const K *key, const V *value)
{
    keys += key;
    values += value;
}

template <typename K, typename V>
std::pair<K, V>& KTools::Kff::Map<K, V>::operator[](const qint64 i)
{
    return {keys[i], values[i]};
}

template <typename K, typename V>
KTools::Kff::Map<K, V>& KTools::Kff::Map<K, V>::operator+=(const std::pair<K, V> &other)
{
    this->append(other.first, other.second);
}

template <typename K, typename V>
void KTools::Kff::Map<K, V>::remove(const qint64 i)
{
    keys->remove(i);
    values->remove(i);
}

template <typename K, typename V>
void KTools::Kff::Map<K, V>::safeRemove(const qint64 i)
{
    keys->safeRemove(i);
    values->safeRemove(i);
}

template <typename K, typename V>
qint64 KTools::Kff::Map<K, V>::size()
{
    return keys->size();
}

template <typename K, typename V>
qint64 KTools::Kff::Map<K, V>::findKey(const K &patt)
{
    return keys->find(patt);
}
