#include "./requesthandler.h"

#include <regex>

#include "socket.h"
#include <iostream>
//#include "../log.h"

void KTools::Network::RequestHandler::set(const int connDescriptor, Socket *sock)
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
    if (socket)
        raw = socket->read(descriptor);
    if (!raw.empty())
    {
        Request info = parseHeader();
        if (info.type != "HEAD")
        {
            request = info;
            handler();
            writeHeader();
            writeBody();
            socket->close(descriptor);
        }
        else
            socket->close(descriptor);
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

void KTools::Network::RequestHandler::start(RequestHandler *obj)
{
    obj->preprocessor();
    delete obj;
}

void KTools::Network::RequestHandler::setStatusCode(const int code)
{
    switch (code)
    {
        case 100: responseCode = "100 Continue"; break;
        case 101: responseCode = "101 Switching Protocols"; break;
        case 200: responseCode = "200 OK"; break;
        case 201: responseCode = "201 Created"; break;
        case 202: responseCode = "202 Accepted"; break;
        case 203: responseCode = "203 Non-Authoritative Information"; break;
        case 204: responseCode = "204 No Content"; break;
        case 205: responseCode = "205 Reset Content"; break;
        case 206: responseCode = "206 Partial Content"; break;
        case 300: responseCode = "300 Multiple Choices"; break;
        case 301: responseCode = "301 Moved Permanently"; break;
        case 302: responseCode = "302 Found"; break;
        case 303: responseCode = "303 See Other"; break;
        case 304: responseCode = "304 Not Modified"; break;
        case 307: responseCode = "307 Temporary Redirect"; break;
        case 308: responseCode = "308 Permanent Redirect"; break;
        case 400: responseCode = "400 Bad Request"; break;
        case 401: responseCode = "401 Unauthorized"; break;
        case 402: responseCode = "402 Payment Required"; break;
        case 403: responseCode = "403 Forbidden"; break;
        case 404: responseCode = "404 Not Found"; break;
        case 405: responseCode = "405 Method Not Allowed"; break;
        case 406: responseCode = "406 Not Acceptable"; break;
        case 407: responseCode = "407 Proxy Authentication Required"; break;
        case 408: responseCode = "408 Request Timeout"; break;
        case 409: responseCode = "409 Conflict"; break;
        case 410: responseCode = "410 Gone"; break;
        case 411: responseCode = "411 Length Required"; break;
        case 412: responseCode = "412 Precondition Failed"; break;
        case 413: responseCode = "413 Content Too Large"; break;
        case 414: responseCode = "414 URI Too Long"; break;
        case 415: responseCode = "415 Unsupported Media Type"; break;
        case 416: responseCode = "416 Range Not Satisfiable"; break;
        case 417: responseCode = "417 Expectation Failed"; break;
        case 418: responseCode = "418 I'm a teapot"; break; // 1st April joke
        case 421: responseCode = "421 Misdirected Request"; break;
        case 422: responseCode = "422 Unprocessable Content"; break;
        case 426: responseCode = "426 Upgrade Required"; break;
        case 500: responseCode = "500 Internal Server Error"; break;
        case 501: responseCode = "501 Not Implemented"; break;
        case 502: responseCode = "502 Bad Gateway"; break;
        case 503: responseCode = "503 Service Unavailable"; break;
        case 504: responseCode = "504 Gateway Timeout"; break;
        case 505: responseCode = "505 HTTP Version Not Supported"; break;
    }
}

template<>
void KTools::Network::RequestHandler::write(const std::string &data)
{
    body += data;
}

void KTools::Network::RequestHandler::writeHeader()
{
    std::string data = httpVersion + responseCode + endLine;
    socket->write(descriptor, data);
    if (body.size() > 0)
    {
        data = "Content-Length: " + std::to_string(body.size()) + endLine;
        socket->write(descriptor, data);
    }
    std::map<std::string, std::string>::const_iterator i;
    for (i = header.begin(); i != header.end(); i++)
    {
        data = i->first + ": " + i->second + endLine;
        socket->write(descriptor, data);
    }
    socket->write(descriptor, endLine);
}

void KTools::Network::RequestHandler::writeBody()
{
    socket->write(descriptor, body);
}

void KTools::Network::RequestHandler::setRoot(const std::string path)
{
    root = path;
}
