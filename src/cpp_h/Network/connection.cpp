#include "./connection.h"

#include <openssl/err.h>
#include <thread>

#include "socket.h"

#include "requesthandler.h"

KTools::Network::Connection::~Connection()
{
    if (sock)
        delete sock;
}

void KTools::Network::Connection::listen(const int port)
{
    if (sock)
        delete sock;

    sock = new Socket();
    sock->setPort(port);
    sock->create();
    sock->setSocketOptions();
    sock->bind();
    while (1)
    {
        sock->listen();
        int connDescriptor = sock->accept();
        RequestHandler *handler = new RequestHandler(connDescriptor, sock);
        std::thread tr(RequestHandler::start, std::ref(handler));
        tr.detach();
    }
}


SSL_CTX* KTools::Network::Connection::createSslContext()
{
    const SSL_METHOD *method = TLS_server_method();
    SSL_CTX *context = SSL_CTX_new(method);
    if (!context)
    {
        ERR_print_errors_fp(stderr);
        return NULL;
    }

    if (SSL_CTX_use_certificate_file(context, "cert.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    if (SSL_CTX_use_PrivateKey_file(context, "key.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    return context;
}
