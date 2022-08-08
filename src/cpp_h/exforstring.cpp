#include "exforstring.h"

#include <iostream>
#include <algorithm>
#include <QString>
#include <QVector>
#include <QRegularExpression>

KTools::ExForString::ExForString() {}

void KTools::ExForString::replace(QString &inp, const QVector<QString> &whatReplace, const QVector<QString> &onWhatReplace)
{
    std::string input = inp.toStdString();
    for (int i = 0; i < whatReplace.size(); i++)
    {
        size_t startPos = 0;
        while ((startPos = input.find(whatReplace[i].toStdString(), startPos)) != std::string::npos)
        {
            input.replace(startPos, whatReplace[i].length(), onWhatReplace[i].toStdString());
            startPos += onWhatReplace[i].length();
        }
    }
    inp = QString::fromStdString(input);
}

void KTools::ExForString::replace(QByteArray &inp, const QVector<QByteArray> &whatReplace, const QVector<QByteArray> &onWhatReplace)
{
    std::string input = inp.toStdString();
    for (int i = 0; i < whatReplace.size(); i++)
    {
        size_t startPos = 0;
        while ((startPos = input.find(whatReplace[i].toStdString(), startPos)) != std::string::npos)
        {
            input.replace(startPos, whatReplace[i].length(), onWhatReplace[i].toStdString());
            startPos += onWhatReplace[i].length();
        }
    }
    inp = QByteArray::fromStdString(input);
}

void KTools::ExForString::deleteChars(QString &inp, const QVector<QString> &whatDelete)
{
    QVector<QString> voids;
    for (int i = 0; i < whatDelete.size(); i++)
        voids.push_back("");
    replace(inp, whatDelete, voids);
}

void KTools::ExForString::executeRegex(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult)
{
    regexResult.resize(pattens.size());
    for (int i = 0; i < pattens.size(); i++)
    {
        QRegularExpression re(pattens[i]);
        QRegularExpressionMatchIterator reI = re.globalMatch(data);
        for (int j = 0; reI.hasNext(); j++)
        {
            regexResult[i].resize(regexResult[i].size() + 1);
            QRegularExpressionMatch match = reI.next();
            for (int jj = 0; jj <= match.lastCapturedIndex(); jj++)
                regexResult[i][j].push_back(match.captured(jj));
        }
    }
}

void KTools::ExForString::executeRegex(const QString &data, const QString &pattern, QVector<QString> &result)
{
    result.clear();
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        result.append(match.captured(1));
    }
}

void KTools::ExForString::executeRegex(const QString &data, const QString &pattern, QVector<double> &result)
{
    result.clear();
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        result.append(match.captured(1).toDouble());
    }
}

void KTools::ExForString::executeRegex(const QString &data, const QString &pattern, QVector<qint64> &result)
{
    result.clear();
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        result.append(match.captured(1).toLong());
    }
}

QVector<qint64> KTools::ExForString::getIntegerNumberFromString(const QString &str)
{
    QVector<qint64> result;
    executeRegex(str, "(\\d+.\\d+)", result);
    return result;
}

QVector<double> KTools::ExForString::getDoubleNumberFromString(const QString &str)
{
    QVector<double> result;
    executeRegex(str, "(\\d+[.,]\\d+|\\d+)", result);
    return result;
}

template<>
void KTools::ExForString::varDump(const bool &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::string tmp;
    if (value)
        tmp = "\"true\"";
    else
        tmp = "\"false\"";
    std::cout << preLine << "bool (" << tmp << ')' << std::endl;
}

template<>
void KTools::ExForString::varDump(const unsigned long &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::cout << preLine << "int (" << value << ')' << std::endl;
}

template<>
void KTools::ExForString::varDump(const int &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::cout << preLine << "int (" << value << ')' << std::endl;
}

template<>
void KTools::ExForString::varDump(const std::string &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::string tmp = '"' + value + '"';
    rmChar(tmp, '\r');
    std::cout << preLine << "std::string (" << value.size() << ')' << std::endl;
    std::cout << preLine << tmp << std::endl;
}

template<>
void KTools::ExForString::varDump(const std::vector<std::string> &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::cout << preLine << "std::vector (" << value.size() << ')' << std::endl << preLine << "{" << std::endl;
    for (int i = 0; i < value.size(); i++)
    {
        varDump<std::string>(value[i], tabs + 1);
    }
    std::cout << preLine << "}" << std::endl;
}

template<>
void KTools::ExForString::varDump(const std::pair<std::string, std::string> &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::pair copy = value;
    rmChar(copy.first, '\r');
    rmChar(copy.second, '\r');
    std::cout << preLine << "[\"" << copy.first << "\"] => \"" << copy.second << "\"" << std::endl;
}

template<>
void KTools::ExForString::varDump(const std::map<std::string, std::string> &value, const int tabs)
{
    std::string preLine;
    preLine.append(tabs, '\t');
    std::cout << preLine << "std::map (" << value.size() << ')' << std::endl << preLine << "{" << std::endl;

    std::map<std::string, std::string>::const_iterator i;
    for (i = value.begin(); i != value.end(); i++)
    {
        std::pair<std::string, std::string> subVal({i->first, i->second});
        varDump<std::pair<std::string, std::string>>(subVal, tabs + 1);
    }
    std::cout << preLine << "}" << std::endl;
}

void KTools::ExForString::rmChar(std::string &string, const char whatRemove)
{
    string.erase(std::remove(string.begin(), string.end(), whatRemove), string.end());
}

void KTools::ExForString::rmTrailingChars(std::string &data, const char whatRemove)
{
    int pos = data.find_last_not_of(whatRemove) + 1;
    if (pos != data.size())
        data.erase(pos, std::string::npos);
}
