#include "./ssl.h"

#include <iostream>

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    SSL_library_init();
    SSL_load_error_strings();
#endif
SSL_CTX* KTools::Network::Ssl::Ssl::sslCtx = nullptr;

KTools::Network::Ssl::Ssl::Ssl(BIO *bioSsl)
{
    BIO_get_ssl(bioSsl, &ssl);
    if (ssl == nullptr)
        std::cout << "Cannot extract SSL struct." << std::endl;
}

void KTools::Network::Ssl::Ssl::setMinProtocolVersion()
{
    SSL_CTX_set_min_proto_version(sslCtx, TLS1_2_VERSION);
}

bool KTools::Network::Ssl::Ssl::setTrustedStorePath()
{
    if (SSL_CTX_set_default_verify_paths(sslCtx) != 1)
    {
        std::cout << "Can not load trusted store." << std::endl;
        return false;
    }
    return true;
}

void KTools::Network::Ssl::Ssl::setHostName(const std::string &hostName)
{
    SSL_set_tlsext_host_name(ssl, hostName.c_str());
}

bool KTools::Network::Ssl::Ssl::verifyCert(const std::string &hostName)
{
    int errorCode = SSL_get_verify_result(ssl);
    if (errorCode != X509_V_OK)
    {
        const char *message = X509_verify_cert_error_string(errorCode);
        std::cout << "Cert verfication error #" << errorCode << ": " << message << std::endl;
        return false;
    }
    X509 *cert = SSL_get_peer_certificate(ssl);
    if (cert == nullptr)
    {
        std::cout << "No certificate was presented by server" << std::endl;
        return false;
    }

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    if (x509_check_host(cert, hostName.data(), hostName.size(), 0, nullptr) != 1)
    {
        std::cout << "Cert verification error: x509_check_host" << std::endl;
        return false;
    }
#endif
    return true;
}

void KTools::Network::Ssl::Ssl::createSslCtx()
{
    sslCtx = SSL_CTX_new(TLS_client_method());
}
