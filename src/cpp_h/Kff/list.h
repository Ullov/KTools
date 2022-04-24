#ifndef KTOOLS_KFF_LIST_H
#define KTOOLS_KFF_LIST_H

#include "string.h"
#include <QList>

namespace KTools::Kff {
    template<typename T>
    class List : private String
    {
    public:
        List(Manager *man); // Creates empty list. See String constructor if does not understand
        List(Manager *man, const qint64 pos);
        List(Pointer *poi);
        ~List();

        void remove(const qint64 i);
        void safeRemove(const qint64 i);
        qint64 size();

        template <typename F>
        qint64 find(const F &patt);

        T& operator[](const qint64 i);
        List<T>& operator+=(const T &other);
        List<T>& operator=(const QList<T> &other);

    private:
        QList<T> list;
        String *parent;
    };
}

#endif // KTOOLS_KFF_LIST_H
