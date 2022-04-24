#ifndef KTOOLS_KFF_STRING_H
#define KTOOLS_KFF_STRING_H

#include <QByteArray>

namespace KTools::Kff {
    class Pointer;
    class Manager;
    class String
    {
    public:
        String(Manager *man);
        String(Manager *man, const qint64 pos);
        String(const Pointer *poi);
        ~String();

        QByteArray mid(const qint64 pos, const qint64 len = -1);
        QByteArray& readAll();
        void insert(const qint64 pos, const QByteArray content);
        char at(const qint64 pos);
        void deleteVariable();
        qint64 size();


        char operator[](const uint pos);
        String& operator=(const QByteArray &other);
        String& operator=(const QString &other);
        bool operator==(const QByteArray &other);
        bool operator==(const QString &other);
        String& operator+=(const QByteArray &other);


    protected:
        void flush();
        String *string = this;
        //Pointer *pointer;

    private:
        QByteArray data;
    };
}

#endif // KTOOLS_KFF_STRING_H
