#include "./socket.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>

KTools::Network::Socket::Socket()
{
	bzero(&servaddr, sizeof(servaddr));
}

bool KTools::Network::Socket::create()
{
	sockfd = socket(domain, socketType, protocol);
    if (sockfd == -1)
    	return false;
    else
    	return true;
}

bool KTools::Network::Socket::setSocketOptions()
{
    if (setsockopt(sockfd, apiLevel, options, &opt, sizeof(opt)))
    	return false;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500;
    if (setsockopt(sockfd, apiLevel, SO_RCVTIMEO, &timeout, sizeof(timeout)))
        return false;
    
    servaddr.sin_family = domain;
    servaddr.sin_addr.s_addr = ip;
    servaddr.sin_port = htons(port);
    return true;
}

bool KTools::Network::Socket::bind()
{
	if (::bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    	return false;
    else
    	return true;
}

bool KTools::Network::Socket::listen(const int queueSize)
{
	if (::listen(sockfd, queueSize) != 0)
		return false;
	else
		return true;
}

int KTools::Network::Socket::accept()
{
	len = sizeof(servaddr);
    connfd = ::accept(sockfd, (struct sockaddr*)&servaddr, &len);
    if (connfd < 0)
        return connfd;
	else
        return connfd;
}

bool KTools::Network::Socket::connect()
{
    if (::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    	return false;
	else
		return true;
}

int KTools::Network::Socket::close(const int connDescriptor)
{
    return ::close(connDescriptor);
}

std::string KTools::Network::Socket::read(const int connDescriptor, const int bufferSize)
{
    std::string res;
    char* buffer = new char[bufferSize];
    res.erase();
    bzero(buffer, bufferSize);
    while (::read(connDescriptor, buffer, bufferSize) > 0)
    {
        res.append(buffer, bufferSize);
        bzero(buffer, bufferSize);
    }
    delete[] buffer;
    return res;
}

int KTools::Network::Socket::write(const int connDescriptor, const char *buffer)
{
    return ::send(connDescriptor, buffer, strlen(buffer), 0);
}

int KTools::Network::Socket::write(const int connDescriptor, const std::string &buffer)
{
    return ::send(connDescriptor, buffer.c_str(), buffer.size(), 0);
}

void KTools::Network::Socket::setIp(const std::string &ipL)
{
    ip = inet_addr(ipL.c_str());
}

void KTools::Network::Socket::setIp(const Address ipL)
{
    ip = static_cast<int>(ipL);
}

void KTools::Network::Socket::setPort(const int portL)
{
	port = portL;
}

void KTools::Network::Socket::setDomain(const Domain domainL)
{
    domain = static_cast<int>(domainL);
}

void KTools::Network::Socket::setSocketType(const SocketType socketTypeL)
{
    socketType = static_cast<int>(socketTypeL);
}

void KTools::Network::Socket::setSocketType(const int socketTypeL)
{
    socketType = socketTypeL;
}

void KTools::Network::Socket::setProtocol(const int protocolL)
{
    protocol = protocolL;
}

void KTools::Network::Socket::setApiLevel(const int apiLevelL)
{
    apiLevel = apiLevelL;
}

void KTools::Network::Socket::setOptions(const int optionsL)
{
    options = optionsL;
}



