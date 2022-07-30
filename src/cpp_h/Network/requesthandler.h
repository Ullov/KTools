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
        RequestHandler(const int connDescriptor, Socket *sock);
        static void start(RequestHandler *obj);

    private:
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
        Request parseHeader();
        void preprocessor();
        void handler(Request &request);

        std::string responeseCode = "200";
        std::string httpVersion = "HTTP/1.1";
        std::map<std::string, std::string> header;
        std::string body = "";
        int descriptor;
        std::string raw;
        Socket *socket;
    };
}

#endif // KTOOLS_NETWORK_REQUEST_HANDLER_H
