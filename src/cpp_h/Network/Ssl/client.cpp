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
    std::cout << '1' << std::endl;
    bio->createConnect(hostName);
    std::cout << '2' << std::endl;
    bio->makeBioSsl();
    std::cout << '3' << std::endl;
    Ssl *ssl = bio->getSslClass();
    std::cout << '4' << std::endl;
    ssl->setHostName(hostName);
    std::cout << '5' << std::endl;
    bio->doHandshake();
    std::cout << '6' << std::endl;
    ssl->verifyCert(hostName);
    std::cout << '7' << std::endl;
    bio->send("GET / HTTP/1.1", hostName);
    std::cout << '8' << std::endl;
    return bio->receive();
}