#ifndef KTOOLS_CONVERTER_H
#define KTOOLS_CONVERTER_H

#include <QtGlobal>

#include <iomanip>

class QByteArray;

namespace KTools
{
    class Converter
    {
    public:
        Converter();

        template<typename T, typename E>
        static E convert(const T &data);

        template<typename T>
        static T byteArrayToT(const QByteArray &bArr);
        template<typename T>
        static QByteArray toByteArray(const T &data);

        static QString numberToUtf8(const quint16 &code); // Converts number in char with same code as number
        static void percentEncodingToString(QString &encodedString);
        static void percentEncodingToString(QByteArray &encodedString);
        static void toNtfsCompatibleString(QString &data);
        static void convertHtmlEntities(QString &inp);
        static void convertHtmlEntities(QByteArray &inp);
        static void convertHtmlHexCodes(QString &data);
        static std::string timeToString(const std::_Put_time<char> &time);
        //static QString nationalEncodingToUtf8(const QByteArray &inputEncoding, const QByteArray &data);
    };
}

#endif // KTOOLS_CONVERTER_H
