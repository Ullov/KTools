#include "header.h"

#include <iomanip>

#include "converter.h"

void KTools::Network::Header::insert(const std::string &key, const std::string &value)
{
    headerMap.insert_or_assign(key, value);
}

void KTools::Network::Header::insert(const std::string &fullLine)
{
    std::size_t pos = fullLine.find(':');
    this->insert(fullLine.substr(0, pos), fullLine.substr(pos + 2));
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
    for (int j = 0; j < setCookieLines.size(); j++)
    {
        result += setCookieLines[j] + "\r\n";
    }
    result += "\r\n";
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

void KTools::Network::Header::setCookie(const std::string &key, const std::string &value, const std::time_t expires, const int maxAge, const std::string &domain, const std::string &path, bool secure, const bool httpOnly, const SameSite sameSite)
{
    std::string line = "Set-Cookie: " + key + '=' + value;
    
    if (expires != 0)
    {
        std::time_t tmp = std::time((std::time_t*)expires);
        std::tm *time = gmtime(&tmp);
        line += KTools::Converter::timeToString(std::put_time(time, "; Expires=%a, %d %b %Y %H:%M:%S GMT"));
    }
    if (maxAge != -1)
    {
        line += "; Max-Age=" + std::to_string(maxAge);
    }
    if (domain != "")
    {
        line += "; Domain=" + domain;
    }
    if (path != "")
    {
        line += "; Path=" + path;
    }
    if (sameSite != SameSite::Lax)
    {
        if (sameSite == SameSite::None)
        {
            secure = true;
            line += "; SameSite=None";
        }
        else if (sameSite == SameSite::Strict)
        {
            line += "; SameSite=Strict";
        }
    }
    if (secure)
    {
        line += "; Secure";
    }
    if (httpOnly)
    {
        line += "; HttpOnly";
    }
    setCookieLines.push_back(line);
}
