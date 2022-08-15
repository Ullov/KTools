#include "client.h"

#include "socket.h"
#include "header.h"

SSL_CTX* KTools::Network::Socket::sslCtx = nullptr;

KTools::Network::Client::Client()
{
    socket = new Socket();
    header = new Header();
}

KTools::Network::Client::~Client()
{
    if (socket)
        delete socket;
    if (header)
        delete header;
}

void KTools::Network::Client::connect()
{
    setType("GET");
    setPath("/");
    setDomainName("google.com");
    header->insert("Host", domainName);
    header->insert("User-Agent", "curl/7.84.0");
    header->insert("Accept", "*/*");

    socket->create();
    socket->setPort(80);
    socket->setDomainName(domainName);
    socket->setInTimeout(0, 10);
    socket->connect();
    std::cout << type + ' ' + path + ' ' + version + "\r\n" + header->toString() << std::endl;
    socket->write(type + ' ' + path + ' ' + version + "\r\n" + header->toString());
    std::cout << socket->read() << std::endl;
}

void KTools::Network::Client::setType(const std::string &typeL)
{
    type = typeL;
}

void KTools::Network::Client::setPath(const std::string &pathL)
{
    path = pathL;
}

void KTools::Network::Client::setDomainName(const std::string &name)
{
    domainName = name;
}

void KTools::Network::Client::setVersion(const std::string &versionL)
{
    version = versionL;
}
