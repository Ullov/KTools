#include "options.h"
#include "Kff/string.h"

KTools::Options::Options() : KTools::Kff::Manager(QDir::currentPath() + "/options.kff", KTools::Kff::Manager::OpenMode::Keep)
{
    using KTools::Converter;
    KTools::Log::assignOptionObject(this);
    if (mode == Kff::Manager::OpenMode::Clear)
    {
        valuesString = new Kff::Map<Kff::String, Kff::String>(this);
        valuesInt64 = new Kff::Map<Kff::String, Kff::Pointer>(this);
        valuesUInt64 = new Kff::Map<Kff::String, Kff::Pointer>(this);

        QByteArray content = valuesString->pointer->getAll();
        content.append(valuesInt64->pointer->getAll());
        content.append(valuesUInt64->pointer->getAll());

        defaultStream->seek(0);
        defaultStream->write(content);

        addVariable("Path:Data", Converter::convert<QString, QByteArray>(QDir::currentPath()));
        addVariable("Path:Log", Converter::convert<QString, QByteArray>(QDir::currentPath()) + "/Log/");
    }
    else
    {
        defaultStream->seek(0);
        QByteArray dataPointers = defaultStream->read(27);
        Kff::Pointer poi(this, dataPointers.mid(0, 9));
        valuesString = new Kff::Map<Kff::String, Kff::String>(&poi);
        poi.setAll(dataPointers.mid(9, 9));
        valuesInt64 = new Kff::Map<Kff::String, Kff::Pointer>(&poi);
        poi.setAll(dataPointers.mid(18, 9));
        valuesUInt64 = new Kff::Map<Kff::String, Kff::Pointer>(&poi);
    }
}

void KTools::Options::updateParam(const QByteArray &name, const QByteArray &value)
{
    qint64 numb = valuesString->findKey(name);
    if (numb == -1)
    {
        KLOG_ERROR("Variable with name " + name + " does not exist.");
        return;
    }
    valuesString->update(numb, value);
}


QByteArray KTools::Options::getStringParam(const QByteArray &name)
{
    qint64 numb = valuesString->findKey(name);
    if (numb == -1)
    {
        KLOG_ERROR("Variable with name " + name + " does not exist.");
        return QByteArray();
    }
    return valuesString->operator[](numb).readAll();
}

void KTools::Options::addVariable(const QByteArray &name, const QByteArray &data)
{
    qint64 numb = valuesString->findKey(name);
    if (numb != -1)
    {
        KLOG_ERROR("Attempt add already existing variable. name: " + name);
        return;
    }

    valuesString->append(name, data);
}

void KTools::Options::addVariable(const QByteArray &name, const qint64 data)
{
    qint64 numb = valuesInt64->findKey(name);
    if (numb != -1)
    {
        KLOG_ERROR("Attempt add already existing variable. name: " + name);
        return;
    }

    Kff::Pointer poi(this, Kff::Pointer::PointerType::FixedTypes, this->manager->getNumbers()->add<qint64>(data));
    Kff::String str(this);
    str = name;
    valuesInt64->append(str, poi);
}

void KTools::Options::addVariable(const QByteArray &name, const quint64 data)
{
    qint64 numb = valuesUInt64->findKey(name);
    if (numb != -1)
    {
        KLOG_ERROR("Attempt add already existing variable. name: " + name);
        return;
    }

    Kff::Pointer poi(this, Kff::Pointer::PointerType::FixedTypes, this->manager->getNumbers()->add<quint64>(data, Kff::FixedTypes::Type::UInt64));
    Kff::String str(this);
    str = name;
    valuesUInt64->append(str, poi);
}

/*template QByteArray KTools::Options::getParam<QByteArray>(const QByteArray&);
template QString KTools::Options::getParam<QString>(const QByteArray&);
template qint8 KTools::Options::getParam<qint8>(const QByteArray&);*/
