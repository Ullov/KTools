#include "./requesthandler.h"

#include <regex>
#include <iostream>

#include "socket.h"
#include "request.h"
#include "response.h"

void KTools::Network::RequestHandler::set(const int connDescriptor, Socket *sock)
{
    socket = sock;
	descriptor = connDescriptor;
}

void KTools::Network::RequestHandler::preprocessor()
{
    std::string raw;
    if (socket)
        raw = socket->read(descriptor);
    if (!raw.empty())
    {
        request = new Request(raw);
        raw.clear();
        if (request->getType() != Request::Type::HEAD)
        {
            response = new Response();
            handler();
            socket->write(descriptor, response->toString());
            socket->close(descriptor);
        }
        else
            socket->close(descriptor);
    }
    if (request != NULL)
        delete request;
    if (response != NULL)
        delete response;
}

void KTools::Network::RequestHandler::start(RequestHandler *obj)
{
    obj->preprocessor();
    delete obj;
}

void KTools::Network::RequestHandler::setRoot(const std::string path)
{
    root = path;
}
