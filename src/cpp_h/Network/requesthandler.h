#ifndef KTOOLS_NETWORK_REQUEST_HANDLER_H
#define KTOOLS_NETWORK_REQUEST_HANDLER_H

#include <string>
#include <map>
#include <vector>

namespace KTools::Network {
    class Socket;
    class RequestHandler
    {
    public:
        RequestHandler(){}

        static void start(RequestHandler *obj);
        void set(const int connDescriptor, Socket *sock);
        virtual RequestHandler* clone() = 0;

    protected:
        struct Request
        {
            std::string type;
            std::string version;
            std::vector<std::string> header;
            std::map<std::string, std::string> headerMap;
            std::map<std::string, std::string> cookies;
            std::string path;
        };

        void appendHeader(const std::string &name, const std::string &value);
        virtual void handler(KTools::Network::RequestHandler::Request &request) = 0;
        void setStatusCode(const int code);

        std::string responseCode = "200 OK";
        std::string httpVersion = "HTTP/1.1";
        std::map<std::string, std::string> header;
        std::string body = "";
        int descriptor = -1;
        std::string raw;
        Socket *socket = NULL;

    private:
        Request parseHeader();
        void preprocessor();
    };
}

#endif // KTOOLS_NETWORK_REQUEST_HANDLER_H
