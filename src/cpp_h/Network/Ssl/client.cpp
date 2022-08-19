#include "./client.h"

#include "./ssl.h"
#include "./bio.h"

#include <iostream>

KTools::Network::Ssl::Client::Client()
{
    if (Ssl::sslCtx == nullptr)
    {
        KTools::Network::Ssl::Ssl::createSslCtx();
        KTools::Network::Ssl::Ssl::setMinProtocolVersion();
        KTools::Network::Ssl::Ssl::setTrustedStorePath();
    }

    bio = new Bio();
}

KTools::Network::Ssl::Client::~Client()
{

}

std::string KTools::Network::Ssl::Client::makeRequest(const std::string &hostName)
{
    bio->createConnect(hostName);
    bio->makeBioSsl();
    Ssl *ssl = bio->getSslClass();
    ssl->setHostName(hostName);
    bio->doHandshake();
    ssl->verifyCert(hostName);
    bio->send("GET / HTTP/1.1", hostName);
    return bio->receive();
}

bool KTools::Network::Ssl::Client::setTimeout(const time_t sec, const time_t usec)
{
    return bio->setInTimeout(sec, usec);
}
