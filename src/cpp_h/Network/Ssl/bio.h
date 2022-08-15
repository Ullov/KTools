#ifndef KTOOLS_NETWORK_SSL_BIO_H
#define KTOOLS_NETWORK_SSL_BIO_H

#include <string>
#include <openssl/bio.h>

namespace KTools::Network::Ssl
{
    class Ssl;
    class Bio
    {
    public:
        Bio();

        void createConnect(const std::string &hostName);
        void makeBioSsl();
        Ssl* getSslClass();
        bool doHandshake();
        void send(const std::string &requestData, const std::string &hostName);
        std::string receive();
    protected:
        BIO *bio = nullptr;
        BIO *bioSsl = nullptr;
    };
}

#endif // KTOOLS_NETWORK_SSL_BIO_H
