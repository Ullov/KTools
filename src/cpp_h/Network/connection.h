#ifndef KTOOLS_NETWORK_CONNECTION_H
#define KTOOLS_NETWORK_CONNECTION_H

#include <openssl/ssl.h>

namespace KTools::Network {
    class Socket;
    class Connection
    {
    public:
        Connection(){}
        ~Connection();

        void listen(const int port);

    private:
        SSL_CTX *createSslContext();
        Socket *sock = NULL;
    };
}

#endif // KTOOLS_NETWORK_CONNECTION_H
