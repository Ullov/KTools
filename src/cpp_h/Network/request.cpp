#include "request.h"

#include <regex>

#include "log.h"
#include "exforstring.h"

KTools::Network::Request::Request(const std::string &rawData)
{
    raw = rawData;
    ExForString::rmChar(raw, '\r');
    std::size_t pos = 0;
    std::size_t newPos = 0;
    std::size_t len = 0;
    bool isFirstLine = true;
    do
    {
        newPos = raw.find("\n", pos);
        len = newPos - pos;
        std::string cut = raw.substr(pos, len);
        if (cut.size() == 0)
            break;
        if (isFirstLine)
        {
            std::regex reg("(^[^ ]+) ([^ ]+) ([^ ]+)");
            std::sregex_iterator begin = std::sregex_iterator(cut.begin(), cut.end(), reg);
            for (std::sregex_iterator i = begin; i != std::sregex_iterator(); i++)
            {
                setType(i->str(1));
                path = i->str(2);
                setHttpVersion(i->str(3));
            }
            isFirstLine = false;
        }
        else
        {
            header.insert(cut);
        }
        pos = newPos + 1;
    }
    while (pos != 0);

    if (pos != 0)
    {
        if (header["Content-Length"] == "")
            setBody(raw.substr(pos + 1));
        else
            setBody(raw.substr(pos + 1, std::atoi(header["Content-Length"].c_str())));
    }

    if (header.find("Cookie") != header.end())
    {
        std::string &rawCookies = header.find("Cookie")->second;
        pos = 0;
        newPos = 0;
        len = 0;
        do
        {
            newPos = rawCookies.find(";", pos);
            len = newPos - pos;
            std::string cut = rawCookies.substr(pos, len);
            if (cut[0] == ' ')
                cut.erase(cut.begin());
            std::size_t equPos = cut.find_first_of('=');
            cookies.insert(cut.substr(0, equPos), cut.substr(equPos + 1));
            pos = newPos + 1;
        }
        while (pos != 0);
    }
}

const std::string& KTools::Network::Request::getPath()
{
    return path;
}

void KTools::Network::Request::setType(const std::string &value)
{
    if (value == "GET")
        type = Type::GET;
    else if (value == "POST")
        type = Type::POST;
    else if (value == "PUT")
        type = Type::PUT;
    else if (value == "PRI")
        type = Type::PRI;
    else
        KLOG_ERROR("Unknown request type: " + QString(value.c_str()));
        
}

const KTools::Network::Request::Type& KTools::Network::Request::getType()
{
    return type;
}

void KTools::Network::Request::setBody(const std::string &data)
{
    body = data;
    if (body.size() == 0 || type != Type::POST)
        return;
    if (header["Content-Type"] == "application/x-www-form-urlencoded")
    {
        int cutStart = 0;
        std::string name = "";
        for (int i = 0; i < body.size(); i++)
        {
            if ((i + 1 == body.size()) && name != "")
            {
                postParams.insert({name, body.substr(cutStart)});
                break;
            }
            switch (body[i])
            {
                case '=':
                {
                    name = body.substr(cutStart, i - cutStart);
                    cutStart = i + 1;
                    break;
                }
                case '&':
                {
                    postParams.insert({name, body.substr(cutStart, i - cutStart)});
                    name = "";
                    cutStart = i + 1;
                    break;
                }
            }
        }
    }
}

void KTools::Network::Request::setHttpVersion(const std::string &value)
{
    if (value == "HTTP/1.1")
        httpVersion = HttpVersion::HTTP11;
    else if (value == "HTTP/1.0")
        httpVersion = HttpVersion::HTTP10;
    else if (value == "HTTP/0.9")
        httpVersion = HttpVersion::HTTP09;
}

const std::string& KTools::Network::Request::getPostParam(const std::string &key)
{
    return postParams[key];
}
