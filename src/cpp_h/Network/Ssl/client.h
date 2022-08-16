#ifndef KTOOLS_NETWORK_SSL_CLIENT_H
#define KTOOLS_NETWORK_SSL_CLIENT_H

#include <string>
#include <openssl/bio.h>

namespace KTools::Network::Ssl
{
    class Bio;
    class Ssl;
    class Client
    {
    public:
        Client();
        ~Client();

        std::string makeRequest(const std::string &hostName);
    protected:
        Bio *bio = nullptr;
        Ssl *ssl = nullptr;
    };
}

#endif // KTOOLS_NETWORK_SSL_CLIENT_H
