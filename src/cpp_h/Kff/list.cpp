#include "list.h"
#include "../converter.h"
#include "pointer.h"
#include "../log.h"

template <typename T>
KTools::Kff::List<T>::List(KTools::Kff::Manager *man) : KTools::Kff::String(man) {}

template <typename T>
KTools::Kff::List<T>::List(KTools::Kff::Manager *man, const qint64 pos) : KTools::Kff::String(man, pos)
{
    for (qint64 i = 0 ; i < this->string->size(); i += sizeof(T))
    {
        list.append(KTools::Converter::byteArrayToT<T>(this->string->mid(i, sizeof(T))));
    }
}

template <>
KTools::Kff::List<KTools::Kff::String>::List(KTools::Kff::Manager *man, const qint64 pos) : KTools::Kff::String(man, pos)
{
    for (qint64 i = 0 ; i < this->string->size(); i += 9)
    {
        Pointer pointer(man, this->string->mid(i, 9));
        list.append(String(&pointer));
    }
}

template <>
KTools::Kff::List<KTools::Kff::Pointer>::List(KTools::Kff::Manager *man, const qint64 pos) : KTools::Kff::String(man, pos)
{
    for (qint64 i = 0 ; i < this->string->size(); i += 9)
    {
        Pointer pointer(man, this->string->mid(i, 9));
        list.append(pointer);
    }
}

template <typename T>
KTools::Kff::List<T>::List(Pointer *poi) : KTools::Kff::String(poi)
{
    for (qint64 i = 0 ; i < this->string->size(); i += sizeof(T))
    {
        list.append(KTools::Converter::byteArrayToT<T>(this->string->mid(i, sizeof(T))));
    }
}

template <>
KTools::Kff::List<KTools::Kff::String>::List(Pointer *poi) : KTools::Kff::String(poi)
{
    for (qint64 i = 0 ; i < this->string->size(); i += 9)
    {
        Pointer pointer(poi->getManager(), this->string->mid(i, 9));
        list.append(String(&pointer));
    }
}

template <>
KTools::Kff::List<KTools::Kff::Pointer>::List(Pointer *poi) : KTools::Kff::String(poi)
{
    for (qint64 i = 0 ; i < this->string->size(); i += 9)
    {
        Pointer pointer(poi->getManager(), this->string->mid(i, 9));
        list.append(pointer);
    }
}

template <typename T>
KTools::Kff::List<T>::~List()
{
    this->string->operator=(QByteArray());
    for (int i = 0; i < list.size(); i++)
    {
        this->string->operator+=(KTools::Converter::toByteArray<T>(list[i]));
    }
}

template <>
KTools::Kff::List<KTools::Kff::String>::~List()
{
    this->string->operator=(QByteArray());
    for (int i = 0; i < list.size(); i++)
    {
        this->string->operator+=(list[i].pointer->getAll());
    }
}

template <>
KTools::Kff::List<KTools::Kff::Pointer>::~List()
{
    this->string->operator=(QByteArray());
    for (int i = 0; i < list.size(); i++)
    {
        this->string->operator+=(list[i].getAll());
    }
}

template <typename T>
T& KTools::Kff::List<T>::operator[](const qint64 i)
{
    return list[i];
}

template <typename T>
KTools::Kff::List<T>& KTools::Kff::List<T>::operator+=(const T &other)
{
    list.append(other);
    return *this;
}

template <typename T>
KTools::Kff::List<T>& KTools::Kff::List<T>::operator=(const QList<T> &other)
{
    list = other;
    return *this;
}

template <typename T>
void KTools::Kff::List<T>::remove(const qint64 i)
{
    list.removeAt(i);
}

template <typename T>
void KTools::Kff::List<T>::safeRemove(const qint64 i)
{
    list.removeAt(i);
}

template <>
void KTools::Kff::List<KTools::Kff::String>::safeRemove(const qint64 i)
{
    list[i].deleteVariable();
    list.removeAt(i);
}

template <>
void KTools::Kff::List<KTools::Kff::Pointer>::safeRemove(const qint64 i)
{
    list[i].deleteData();
    list.removeAt(i);
}

template <typename T>
qint64 KTools::Kff::List<T>::size()
{
    return list.size();
}

template <>
template <>
qint64 KTools::Kff::List<KTools::Kff::String>::find(const QString &patt)
{
    for (qint64 i = 0; i < this->size(); i++)
    {
        //KLOG_DEBUG(list[i].readAll() + '\n' + patt);
        if (list[i] == patt)
            return i;
    }
    return -1; // Element does not exist
}

template <>
template <>
qint64 KTools::Kff::List<KTools::Kff::String>::find(const QByteArray &patt)
{
    for (qint64 i = 0; i < this->size(); i++)
    {
        KLOG_DEBUG(list[i].readAll() + '\n' + patt);
        if (list[i] == patt)
            return i;
    }
    return -1; // Element does not exist
}

template <>
template <>
qint64 KTools::Kff::List<KTools::Kff::Pointer>::find(const qint64 &patt)
{
    for (qint64 i = 0; i < this->size(); i++)
    {
        qint64 numb = list[i].getData<qint64>();
        if (numb == patt)
            return i;
    }
    return -1; // Element does not exist
}

template <>
template <>
qint64 KTools::Kff::List<KTools::Kff::String>::find(const qint64 &patt)
{
    for (qint64 i = 0; i < this->size(); i++)
    {
        QByteArray numb = KTools::Converter::toByteArray<qint64>(patt);
        if (list[i] == numb)
            return i;
    }
    return -1; // Element does not exist
}

template <>
template <>
qint64 KTools::Kff::List<KTools::Kff::Pointer>::find(const quint64 &patt)
{
    for (qint64 i = 0; i < this->size(); i++)
    {
        quint64 numb = list[i].getData<quint64>();
        if (numb == patt)
            return i;
    }
    return -1; // Element does not exist
}

template void KTools::Kff::List<qint8>::safeRemove(const qint64);
template void KTools::Kff::List<qint16>::safeRemove(const qint64);
template void KTools::Kff::List<qint32>::safeRemove(const qint64);
template void KTools::Kff::List<qint64>::safeRemove(const qint64);
template void KTools::Kff::List<quint8>::safeRemove(const qint64);
template void KTools::Kff::List<quint16>::safeRemove(const qint64);
template void KTools::Kff::List<quint32>::safeRemove(const qint64);
template void KTools::Kff::List<quint64>::safeRemove(const qint64);
template void KTools::Kff::List<double>::safeRemove(const qint64);
template void KTools::Kff::List<bool>::safeRemove(const qint64);

template qint64 KTools::Kff::List<KTools::Kff::Pointer>::size();
template qint64 KTools::Kff::List<qint64>::size();

template KTools::Kff::List<KTools::Kff::Pointer>& KTools::Kff::List<KTools::Kff::Pointer>::operator+=(const KTools::Kff::Pointer&);
template KTools::Kff::List<qint64>& KTools::Kff::List<qint64>::operator+=(const qint64&);
template KTools::Kff::List<KTools::Kff::String>& KTools::Kff::List<KTools::Kff::String>::operator+=(const KTools::Kff::String&);

template KTools::Kff::Pointer& KTools::Kff::List<KTools::Kff::Pointer>::operator[](const qint64);
template KTools::Kff::String& KTools::Kff::List<KTools::Kff::String>::operator[](const qint64);
template qint64& KTools::Kff::List<qint64>::operator[](const qint64);

template KTools::Kff::List<qint64>& KTools::Kff::List<qint64>::operator=(const QList<qint64>&);

template KTools::Kff::List<qint64>::List(KTools::Kff::Pointer*);
template KTools::Kff::List<KTools::Kff::String>::List(KTools::Kff::Manager*);
template KTools::Kff::List<KTools::Kff::Pointer>::List(KTools::Kff::Manager*);

template KTools::Kff::List<qint64>::~List();
