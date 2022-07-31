#ifndef KTOOLS_NETWORK_CONNECTION_H
#define KTOOLS_NETWORK_CONNECTION_H

#include <openssl/ssl.h>

namespace KTools::Network {
    class Socket;
    class RequestHandler;
    class Connection
    {
    public:
        Connection(RequestHandler *handleClass);
        ~Connection();

        void listen(const int port);

    private:
        SSL_CTX *createSslContext();
        Socket *sock = NULL;
        RequestHandler *handler;
    };
}

#endif // KTOOLS_NETWORK_CONNECTION_H
