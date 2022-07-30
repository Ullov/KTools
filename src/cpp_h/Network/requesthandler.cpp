#include "./requesthandler.h"

#include <regex>

#include "socket.h"

KTools::Network::RequestHandler::RequestHandler(const int connDescriptor, Socket *sock)
{
    socket = sock;
	descriptor = connDescriptor;
}

void KTools::Network::RequestHandler::appendHeader(const std::string &name, const std::string &value)
{
	header.insert({name, value});
}

void KTools::Network::RequestHandler::preprocessor()
{
    raw = socket->read(descriptor);
    if (!raw.empty())
    {
        Request info = parseHeader();
        if (info.type != "HEAD")
            handler(info);
    }
}

KTools::Network::RequestHandler::Request KTools::Network::RequestHandler::parseHeader()
{
    std::vector<std::string> header;
    std::size_t pos = 0;
    std::size_t newPos = 0;
    std::size_t len = 0;
    do
    {
        newPos = raw.find("\n", pos);
        len = newPos - pos;
        std::string cut = raw.substr(pos, len);
        if (cut.size() == 1)
            break;
        header.push_back(cut);
        pos = newPos + 1;
    }
    while (pos != 0);

    Request info;
    info.header = header;
    std::regex reg("(^[^ ]+) ([^ ]+) ([^ ]+)");
    std::sregex_iterator begin = std::sregex_iterator(info.header[0].begin(), info.header[0].end(), reg);
    for (std::sregex_iterator i = begin; i != std::sregex_iterator(); i++)
    {
        info.type = i->str(1);
        info.path = i->str(2);
        info.version = i->str(3);
    }
    info.header.erase(info.header.begin());

    for (int i = 0; i < info.header.size(); i++)
    {
        std::string &item = info.header[i];
        int pos = item.find_first_of(':');
        info.headerMap.insert({item.substr(0, pos), item.substr(pos + 2)});
    }
    if (info.headerMap.find("Cookie") != info.headerMap.end())
    {
        std::string &rawCookies = info.headerMap.find("Cookie")->second;
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
            info.cookies.insert({cut.substr(0, equPos), cut.substr(equPos + 1)});
            pos = newPos + 1;
        }
        while (pos != 0);
    }
    return info;
}

void KTools::Network::RequestHandler::handler(Request &request)
{
    std::string resp;
    resp += "HTTP/1.1 200 OK\n";
    resp += "Version: HTTP/1.1\n";
    resp += "Content-Type: text/html; charset=utf-8\n";
    resp += "Content-Length: 17\n\n";
    resp += "<bold>Died</bold>\n";
    socket->write(descriptor, resp);
    socket->close(descriptor);
}

void KTools::Network::RequestHandler::start(RequestHandler *obj)
{
    obj->preprocessor();
    delete obj;
}
