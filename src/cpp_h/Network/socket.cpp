#include "./socket.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>

#include "exforstring.h"

#ifdef KT_DEBUG
#include <iostream>
#endif

KTools::Network::Socket::Socket()
{
	bzero(&servaddr, sizeof(servaddr));
}

KTools::Network::Socket::~Socket()
{
	::close(sockfd);
}

bool KTools::Network::Socket::create()
{
	sockfd = socket(static_cast<int>(protocolFamily), socketType, protocol);
    if (sockfd == -1)
    {
#ifdef KT_DEBUG
        std::cout << "Failed to create socket." << std::endl;
#endif
    	return false;
    }
    else
    {
        static const int opt = 1;
        setOption(SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        setInTimeout(500);
    	return true;
    }
}

bool KTools::Network::Socket::bind()
{
	if (::bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
#ifdef KT_DEBUG
        std::cout << "Failed to bind socket." << std::endl;
#endif
    	return false;
    }
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
    {
#ifdef KT_DEBUG
        std::cout << "Failed to connect socket." << std::endl;
#endif
    	return false;
    }
	else
		return true;
}

int KTools::Network::Socket::close(const int connDescriptor)
{
    return ::close(connDescriptor);
}

std::string KTools::Network::Socket::read(const int connDescriptor)
{
    std::string res;
    char* buffer = new char[bufferSize];
    res.erase();
    bzero(buffer, bufferSize);
    while (::read(connDescriptor, buffer, bufferSize) > 0)
    {
        res.append(buffer, bufferSize);
        buffer[bufferSize + 1] = 0;
        bzero(buffer, bufferSize);
    }
    delete[] buffer;
    KTools::ExForString::rmTrailingChars(res, 0);
    return res;
}

std::string KTools::Network::Socket::read()
{
    std::string res;
    char* buffer = new char[bufferSize];
    res.erase();
    bzero(buffer, bufferSize);
    while (::read(sockfd, buffer, bufferSize) > 0)
    {
        res.append(buffer, bufferSize);
        buffer[bufferSize + 1] = 0;
        bzero(buffer, bufferSize);
    }
    delete[] buffer;
    KTools::ExForString::rmTrailingChars(res, 0);
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

int KTools::Network::Socket::write(const char *buffer)
{
    return ::write(sockfd, buffer, strlen(buffer));
}

int KTools::Network::Socket::write(const std::string &buffer)
{
    return ::write(sockfd, buffer.c_str(), buffer.size());
}

void KTools::Network::Socket::setPort(const int portL)
{
    servaddr.sin_port = htons(portL);
	port = portL;
}

void KTools::Network::Socket::setProtocolFamily(const ProtocolFamily protocolL)
{
    servaddr.sin_family = static_cast<int>(protocolL);
    protocolFamily = protocolL;
}

void KTools::Network::Socket::setSocketType(const SocketType socketTypeL)
{
    socketType = static_cast<int>(socketTypeL);
}

void KTools::Network::Socket::setProtocol(const int protocolL)
{
    protocol = protocolL;
}

void KTools::Network::Socket::setApiLevel(const Level apiLevelL)
{
    apiLevel = static_cast<int>(apiLevelL);
}

bool KTools::Network::Socket::setOption(const int name, const void *value, socklen_t valueSize)
{
    return setsockopt(sockfd, apiLevel, name, value, valueSize);
}

bool KTools::Network::Socket::setInTimeout(const time_t usec, const time_t sec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    return setOption(SO_RCVTIMEO, &timeout, sizeof(timeout));
}

bool KTools::Network::Socket::setOutTimeout(const time_t usec, const time_t sec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    return setOption(SO_SNDTIMEO, &timeout, sizeof(timeout));
}

void KTools::Network::Socket::setDomainName(const std::string &name)
{
    servaddr.sin_addr.s_addr = inet_addr(name.c_str());
}

void KTools::Network::Socket::setBufferSize(const int size)
{
    bufferSize = size;
}
