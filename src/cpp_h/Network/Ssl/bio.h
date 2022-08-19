#ifndef KTOOLS_NETWORK_SSL_BIO_H
#define KTOOLS_NETWORK_SSL_BIO_H

#include <string>
#include <openssl/bio.h>

namespace KTools::Network
{
    class Header;
}

namespace KTools::Network::Ssl
{
    class Ssl;
    class Bio
    {
    public:
        Bio();
        ~Bio();

        void createConnect(const std::string &hostName);
        void makeBioSsl();
        Ssl* getSslClass();
        bool doHandshake();
        void send(const std::string &requestData, const std::string &hostName);
        std::string receive();
        bool setInTimeout(const time_t sec, const time_t usec = 0);
    protected:
        BIO *bio = nullptr;
        BIO *bioSsl = nullptr;
        Header *header = nullptr;
    };
}

#endif // KTOOLS_NETWORK_SSL_BIO_H
