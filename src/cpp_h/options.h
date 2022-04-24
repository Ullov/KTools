#ifndef KTOOLS_OPTIONS_H
#define KTOOLS_OPTIONS_H

#include <QVariant>
#include <QDir>
#include "Kff/manager.h"
#include "Kff/fixedtypes.h"
#include "Kff/variabletypes.h"
#include "Kff/map.h"

namespace KTools
{
    class Options : private KTools::Kff::Manager
    {
    public:
        Options();

        void updateParam(const QByteArray &name, const QByteArray &value);

        QByteArray getStringParam(const QByteArray &name);
        qint64 getInt64Param(const QByteArray &name);
        quint64 getUInt64Param(const QByteArray &name);

        using KTools::Kff::Manager::mode;

        void addVariable(const QByteArray &name, const QByteArray &data); // String
        void addVariable(const QByteArray &name, const qint64 data); // int64
        void addVariable(const QByteArray &name, const quint64 data); // uint64

    private:
        Kff::Map<Kff::String, Kff::String> *valuesString;
        Kff::Map<Kff::String, Kff::Pointer> *valuesInt64;
        Kff::Map<Kff::String, Kff::Pointer> *valuesUInt64;

        Manager* manager = this;
    };
}

#endif // KTOOLS_OPTIONS_H
