#ifndef KTOOLS_NETWORK_CONNECTION_H
#define KTOOLS_NETWORK_CONNECTION_H

#include <openssl/ssl.h>
#include <string>

namespace KTools::Network {
    class Socket;
    class RequestHandler;
    class Connection
    {
    public:
        Connection(RequestHandler *handleClass);
        ~Connection();

        void listen(const int port);
        void setRoot(const std::string &path);

    private:
        SSL_CTX *createSslContext();
        Socket *sock = NULL;
        RequestHandler *handler;
        std::string root;
    };
}

#endif // KTOOLS_NETWORK_CONNECTION_H
