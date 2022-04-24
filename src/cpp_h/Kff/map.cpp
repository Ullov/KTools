#include "map.h"
#include "pointer.h"
#include "list.h"
#include "string.h"

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(KTools::Kff::Manager *man) : KTools::Kff::String(man)
{
    keys = new List<K>(man);
    values = new List<V>(man);
    this->string->operator=(keys-> pointer->getAll());
    this->string->operator+=(keys->pointer->getAll());
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(KTools::Kff::Manager *man, const qint64 pos) : KTools::Kff::String(man, pos)
{
    Pointer lPointer(man, this->string->mid(0, 9));
    keys = new List<K>(man, lPointer);
    lPointer.setAll(this->string->mid(9, 9));
    values = new List<V>(man, lPointer);
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::Map(Pointer *poi) : KTools::Kff::String(poi)
{
    Pointer lPointer(poi->getManager(), this->string->mid(0, 9));
    keys = new List<K>(&lPointer);
    lPointer.setAll(this->string->mid(9, 9));
    values = new List<V>(&lPointer);
    /*keys = new List<K>(poi);
    values = new List<V>(poi);*/
}

template <typename K, typename V>
KTools::Kff::Map<K, V>::~Map()
{
    delete keys;
    delete values;
}

template <typename K, typename V>
void KTools::Kff::Map<K, V>::append(const K &key, const V &value)
{
    keys += key;
    values += value;
}

template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::Pointer>::append(const String &key, const Pointer &value)
{
    keys->operator+=(key);
    values->operator+=(value);
}

template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::append(const QString &key, const QString &value)
{
    String f(pointer->getManager());
    f = key;
    String s(pointer->getManager());
    s = value;
    keys->operator+=(f);
    values->operator+=(s);
}

template <typename K, typename V>
V& KTools::Kff::Map<K, V>::operator[](const qint64 i)
{
    return values->operator[](i);
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
template <typename F>
qint64 KTools::Kff::Map<K, V>::findKey(const F &patt)
{
    return keys->find(patt);
}

template <>
template <>
qint64 KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::findKey(const QString &patt)
{
    return keys->find(patt);
}

template <>
template <>
qint64 KTools::Kff::Map<KTools::Kff::Pointer, KTools::Kff::String>::findKey(const qint64 &patt)
{
    return keys->find(patt);
}

template <>
template <>
qint64 KTools::Kff::Map<KTools::Kff::Pointer, KTools::Kff::String>::findKey(const quint64 &patt)
{
    return keys->find(patt);
}

template <>
template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::update<QByteArray, QByteArray>(const QByteArray &key, const QByteArray &upd)
{
    values->operator[](this->findKey(key)) = upd;
}

template <>
template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::update<qint64, QByteArray>(const qint64 &key, const QByteArray &upd)
{
    values->operator[](this->findKey(key)) = upd;
}

template <>
template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::Pointer>::update<QByteArray, qint64>(const QByteArray &key, const qint64 &upd)
{
    values->operator[](this->findKey(key)).writeData(upd);
}

template <>
template <>
void KTools::Kff::Map<KTools::Kff::String, KTools::Kff::Pointer>::update<QByteArray, quint64>(const QByteArray &key, const quint64 &upd)
{
    values->operator[](this->findKey(key)).writeData(upd);
}

template <typename K, typename V>
KTools::Kff::Pointer& KTools::Kff::Map<K, V>::getPointer()
{
    return this->parent->pointer;
}

template KTools::Kff::String& KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::operator[](const qint64);
template KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::Map(KTools::Kff::Manager*);
template KTools::Kff::Map<KTools::Kff::String, KTools::Kff::Pointer>::Map(KTools::Kff::Manager*);
template KTools::Kff::Map<KTools::Kff::String, KTools::Kff::String>::Map(KTools::Kff::Pointer*);
template KTools::Kff::Map<KTools::Kff::String, KTools::Kff::Pointer>::Map(KTools::Kff::Pointer*);
