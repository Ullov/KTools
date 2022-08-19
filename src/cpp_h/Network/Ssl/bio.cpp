#include "./bio.h"

#include "./ssl.h"
#include "../header.h"

#include <iostream>

#include <openssl/err.h>
#include <sys/socket.h>

KTools::Network::Ssl::Bio::Bio()
{
    header = new Header();
}

KTools::Network::Ssl::Bio::~Bio()
{
    if (header != nullptr)
        delete header;
}

void KTools::Network::Ssl::Bio::createConnect(const std::string &hostName)
{
    bio = BIO_new_connect((hostName + ":443").c_str());
}

void KTools::Network::Ssl::Bio::makeBioSsl()
{
    bioSsl = BIO_push(BIO_new_ssl(KTools::Network::Ssl::Ssl::sslCtx, 1), bio);
}

bool KTools::Network::Ssl::Bio::doHandshake()
{
    if (BIO_do_handshake(bioSsl) <= 0)
    {
        std::cout << "Error while ssl handshaking." << std::endl;
        return false;
    }
    return true;
}

KTools::Network::Ssl::Ssl* KTools::Network::Ssl::Bio::getSslClass()
{
    return new KTools::Network::Ssl::Ssl(bioSsl);
}

void KTools::Network::Ssl::Bio::send(const std::string &requestData, const std::string &hostName)
{
    std::string request = requestData + "\r\n";
    request += "Host: " + hostName + "\r\n";
    request += "Accept-Encoding: identity\r\n\r\n";

    BIO_write(bioSsl, request.data(), request.size());
    BIO_flush(bioSsl);
}

std::string KTools::Network::Ssl::Bio::receive()
{
    std::string result;
    int len = 1;
    std::size_t bodySize = std::string::npos;
    while (1)
    {
        char buffer[4096];
        int len = BIO_read(bioSsl, buffer, sizeof(buffer));
        if (len < 0)
        {
            std::cout << "Negative response len." << std::endl;
            
            BIO *errBio = BIO_new(BIO_s_mem());
            ERR_print_errors(errBio);
            char *buffer;
            std::size_t len = BIO_get_mem_data(bioSsl, &buffer);
            std::string res(buffer, len);
            BIO_free(errBio);

            break;
        }
        else if (len > 0)
        {
            if (bodySize != std::string::npos)
            {
                result += std::string(buffer, len);
                if (header->operator[]("Transfer-Encoding") == "chunked" && result.ends_with("\r\n\r\n"))
                {
                    result.resize(result.size() - 7);
                    break;
                }
                else if (header->operator[]("Transfer-Encoding") != "chunked" && bodySize <= result.size())
                    break;
            }
            else
            {
                result += std::string(buffer, len);
                bool condRes = result.contains("\r\n\r\n");
                if (condRes)
                {
                    header->fromRawString(result);
                    bodySize = std::atoi(header->operator[]("Content-Length").c_str());
                    if (bodySize > 0)
                    {
                        std::size_t pos = result.find("\r\n\r\n");
                        result = result.substr(pos);
                        if (bodySize <= result.size())
                            break;
                    }
                    else if (header->operator[]("Transfer-Encoding") == "chunked")
                    {
                        std::size_t pos = result.find("\r\n\r\n");
                        bodySize = std::stoi(result.substr(pos + 4, 4), nullptr, 16);
                        result = result.substr(pos + 10);
                        if (bodySize <= result.size())
                            break;
                    }
                }
            }
        }
        else if (BIO_should_retry(bio))
            result += this->receive();
        
        if (len < 1)
            break;
    }
    return result;
}

bool KTools::Network::Ssl::Bio::setInTimeout(const time_t sec, const time_t usec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    int fd = -1;
    BIO_get_fd(bioSsl, &fd);
    if (fd >= 0)
    {
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        return true;
    }
    else
    {
        std::cout << "Failed to get socket file descriptor" << std::endl;
        return false;
    }
}
