#ifndef KTOOLS_NETWORK_REQUEST_HANDLER_H
#define KTOOLS_NETWORK_REQUEST_HANDLER_H

#include <string>
#include <map>
#include <vector>

#include "cookies.h"
#include "header.h"

namespace KTools::Network {
    class Socket;
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
        struct Request
        {
            std::string type;
            std::string version;
            Header header;
            Cookies cookies;
            std::string path;
            std::string body;
            std::map<std::string, std::string> parameters;
        };

        void appendHeader(const std::string &name, const std::string &value);
        virtual void handler() = 0;
        void setStatusCode(const int code);
        template <typename T>
        void write(const T &data);


        std::string raw = "";
        Request request;
        std::string root;

    private:
        Request parseHeader();
        void preprocessor();
        void writeHeader();
        void writeBody();
        void parseBody();

        std::string responseCode = "200 OK";
        std::string httpVersion = "HTTP/1.1";
        std::map<std::string, std::string> header;
        std::string body = "";
        int descriptor = -1;
        Socket *socket = NULL;
        static constexpr char endLine[] = "\r\n";
    };
}

#endif // KTOOLS_NETWORK_REQUEST_HANDLER_H
