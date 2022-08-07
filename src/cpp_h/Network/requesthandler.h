#ifndef KTOOLS_NETWORK_REQUEST_HANDLER_H
#define KTOOLS_NETWORK_REQUEST_HANDLER_H

#include <string>
#include <map>
#include <vector>

//#include "cookies.h"
//#include "header.h"

namespace KTools::Network {
    class Socket;
    class Request;
    class Response;
    class RequestHandler
    {
    public:
        RequestHandler(){}
        virtual ~RequestHandler(){}

        static void start(RequestHandler *obj);
        void set(const int connDescriptor, Socket *sock);
        void setRoot(const std::string path);
        virtual RequestHandler* clone() = 0;

    protected:
        virtual void handler() = 0;

        std::string root;
        Request *request = NULL;
        Response *response = NULL;

    private:
        void preprocessor();

        int descriptor = -1;
        Socket *socket = NULL;
    };
}

#endif // KTOOLS_NETWORK_REQUEST_HANDLER_H
