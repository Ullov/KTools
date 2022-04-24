#ifndef KTOOLS_OPTIONS_H
#define KTOOLS_OPTIONS_H

#include <QVariant>
#include <QDir>

namespace KTools
{
    class Options
    {
    public:
        Options();

        //void updateParam(const QByteArray &name, const QByteArray &value);

        //QByteArray getStringParam(const QByteArray &name);
        //qint64 getInt64Param(const QByteArray &name);
        //quint64 getUInt64Param(const QByteArray &name);

        //void addVariable(const QByteArray &name, const QByteArray &data); // String
        //void addVariable(const QByteArray &name, const qint64 data); // int64
        //void addVariable(const QByteArray &name, const quint64 data); // uint64
    };
}

#endif // KTOOLS_OPTIONS_H
