#ifndef KTOOLS_NETWORK_SSL_SSL_H
#define KTOOLS_NETWORK_SSL_SSL_H

#include <string>
//#include <iostream>
#include <openssl/ssl.h>
#include <openssl/bio.h>

namespace KTools::Network::Ssl
{
    class Ssl
    {
    public:
        Ssl(BIO *bioSsl);

        static void setMinProtocolVersion();
        static bool setTrustedStorePath();
        void setHostName(const std::string &hostName);
        bool verifyCert(const std::string &hostName);
        static void createSslCtx();
        
        static SSL_CTX *sslCtx;
    protected:
        SSL *ssl = nullptr;
    };
}

#endif // KTOOLS_NETWORK_SSL_SSL_H
