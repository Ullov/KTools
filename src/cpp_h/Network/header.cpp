#include "header.h"

void KTools::Network::Header::insert(const std::string &key, const std::string &value)
{
    headerMap.insert({key, value});
}

void KTools::Network::Header::insert(const std::string &fullLine)
{
    std::size_t pos = fullLine.find(':');
    this->insert(fullLine.substr(0, pos), fullLine.substr(pos));
}

std::string& KTools::Network::Header::operator[](const std::string &key)
{
    return headerMap[key];
}
std::string KTools::Network::Header::toString()
{
    std::string result;
    std::map<std::string, std::string>::const_iterator i;
    for (i = headerMap.begin(); i != headerMap.end(); i++)
    {
        result += i->first + ": " + i->second + "\r\n";
    }
    return result;
}

void KTools::Network::Header::erase(std::map<std::string, std::string>::iterator i)
{
    headerMap.erase(i);
}

std::map<std::string, std::string>::iterator KTools::Network::Header::begin()
{
    return headerMap.begin();
}

std::map<std::string, std::string>::iterator KTools::Network::Header::end()
{
    return headerMap.end();
}

std::map<std::string, std::string>::iterator KTools::Network::Header::find(const std::string &key)
{
    return headerMap.find(key);
}
