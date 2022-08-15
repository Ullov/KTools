#ifndef KTOOLS_NETWORK_CLIENT_H
#define KTOOLS_NETWORK_CLIENT_H

#include <string>
#include <iostream>

namespace KTools::Network
{
    class Socket;
    class Header;
    class Client
    {
    public:
        Client();
        ~Client();

        Header* header = nullptr;
        
        void connect();
        void setType(const std::string &typeL);
        void setPath(const std::string &pathL);
        void setDomainName(const std::string &name);
        void setVersion(const std::string &versionL);
    protected:
        Socket *socket = nullptr;

        std::string type = "GET";
        std::string path = "/";
        std::string domainName;
        std::string version = "HTTP/1.1";
    };
}

#endif // KTOOLS_NETWORK_CLIENT_H