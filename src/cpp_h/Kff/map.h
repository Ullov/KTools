#ifndef KTOOLS_KFF_MAP_H
#define KTOOLS_KFF_MAP_H

#include "string.h"

namespace KTools::Kff {
    template <typename T>
    class List;
    template <typename K, typename V>
    class Map : private String
    {
    public:
        Map(Manager *man); // Creating new variable
        Map(Manager *man, const qint64 pos); // Finds varianle by position
        Map(Pointer *poi); // Finds variable by pointer
        ~Map();

        void append(const K &key, const V &value);
        void append(const QString &key, const QString &value);
        void remove(const qint64 i);
        void safeRemove(const qint64 i);
        qint64 size();

        template <typename F>
        qint64 findKey(const F &patt);
        template <typename F, typename S>
        void update(const F &key, const S &upd);
        Pointer& getPointer();

        V& operator[](const qint64 i);
        Map<K, V>& operator+=(const std::pair<K, V> &other);


    private:
        List<K> *keys;
        List<V> *values;

        String *parent;
    };
}

#endif // KTOOLS_KFF_MAP_H
