#ifndef KTOOLS_OPTIONS_H
#define KTOOLS_OPTIONS_H

#include <QVariant>
#include <QDir>
#include "Kff/manager.h"
#include "Kff/fixedtypes.h"
#include "Kff/variabletypes.h"

namespace KTools
{
    class Options : private KTools::Kff::Manager
    {
    public:
        Options();
        enum class ParamType : qint8 {
            Int8 = 1,
            Int16 = 2,
            Int32 = 3,
            Int64 = 4,
            UInt8 = 5,
            UInt16 = 6,
            UInt32 = 7,
            UInt64 = 8,
            Float = 9,
            Bool = 10,
            String = 11,
            List = 12
        };

        void updateParam(const QByteArray &name, const QByteArray &value, const ParamType type);
        template <typename T>
        T getParam(const QByteArray &name);

    private:
        void addInt8Variable(const QByteArray &name, const qint8 data);
        void addStringVariable(const QByteArray &name, const QByteArray &data);
        void addInt16Variable(const QByteArray &name, const qint16 data);
        void addInt32Variable(const QByteArray &name, const qint32 data);
        void addInt64Variable(const QByteArray &name, const qint64 data);
    };
}

#endif // KTOOLS_OPTIONS_H
