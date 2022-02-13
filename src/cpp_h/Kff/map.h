#ifndef KTOOLS_KFF_MAP_H
#define KTOOLS_KFF_MAP_H

#include "string.h"
#include "list.h"

namespace KTools::Kff {
    template <typename K, typename V>
    class Map : private String
    {
    public:
        Map(Manager *man); // Creating new variable
        Map(Manager *man, const qint64 pos); // Finds varianle by position
        Map(Pointer *poi); // Finds variable by pointer
        ~Map();

        void append(const K *key, const V *value);
        void remove(const qint64 i);
        void safeRemove(const qint64 i);
        qint64 size();

        std::pair<K, V>& operator[](const qint64 i);
        Map<K, V>& operator+=(const std::pair<K, V> &other);

    private:
        List<K> *keys;
        List<V> *values;
    };
}

#endif // KTOOLS_KFF_MAP_H
