#ifndef KTOOLS_NETWORK_SOCKET_H
#define KTOOLS_NETWORK_SOCKET_H

#include <string>
#include <netinet/in.h>

namespace KTools::Network {
    class Socket
    {
    public:
        enum class Domain : int {
            Unix = AF_UNIX,             // Local communication
            Local = AF_LOCAL,           // Same as Unix
            Inet = AF_INET,             // IPv4 Protocol
            Ax25 = AF_AX25,             // Ameteur radio AX.25 protocol
            Ipx = AF_IPX,               // IPX - Novell protocols
            AppleTalk = AF_APPLETALK,   // Appletalk
            Netrom = AF_NETROM,         // AX.25 packet layer protocol.
            Bridge = AF_BRIDGE,         // Can't be used for creating sockets; mostly used for bridge links
            Atmpvc = AF_ATMPVC,         // Access to raw ATM Permanent Virtual Circuits (PVCs)
            X25 = AF_X25,               // ITU-T X.25 / ISO-8208 protocol
            Inet6 = AF_INET6,           // IPv6 Internet protocols
            Rose = AF_ROSE,             // RATS (Radio Amateur Telecommunications Society) Open Systems environment (ROSE) AX.25 packet layer protocol.
            DecNet = AF_DECnet,         // DECnet protocol sockets
            Key = AF_KEY,               // Key management protocol, originally developed for usage with IPsec
            Netlink = AF_NETLINK,       // Kernel user interface device
            Packet = AF_PACKET,         // Low-level packet interface
            Atmsvc = AF_ATMSVC,         // Access to ATM Switched Virtual Circuits (SVCs)
            Rds = AF_RDS,               // Reliable Datagram Sockets (RDS) protocol
            Pppox = AF_PPPOX,           // Generic PPP transport layer, for setting up L2 tunnels (L2TP and PPPoE)
            Llc = AF_LLC,               // Logical link control (IEEE 802.2 LLC) protocol
            Ib = AF_IB,                 // InfiniBand native addressing
            Mpls = AF_MPLS,             // Multiprotocol Label Switching
            Can = AF_CAN,               // Controller Area Network automotive bus protocol
            Tipc = AF_TIPC,             // TIPC, "cluster domain sockets" protocol
            Bluetooth = AF_BLUETOOTH,   // Bluetooth low-level socket protocol
            Iucv = AF_IUCV,             // IUCV (inter-user communication vehicle) z/VM protocol for hypervisor-guest interaction
            RxRpc = AF_RXRPC,           // Rx, Andrew File System remote procedure call protocol
            Isdn = AF_ISDN,             // New "modular ISDN" driver interface protocol
            Phonet = AF_PHONET,         // Nokia cellular modem IPC/RPC interface
            Ieee802154 = AF_IEEE802154, // IEEE 802.15.4 WPAN (wireless personal area network) raw packet protocol
            Caif = AF_CAIF,             // Ericsson's Communication CPU to Application CPU interface (CAIF) protocol
            Alg = AF_ALG,               // Interface to kernel crypto API
            VSock = AF_VSOCK,           // VSOCK (originally "VMWare VSockets") protocol for hypervisor-guest communication
            Kcm = AF_KCM,               // KCM (kernel connection multiplexer) interface
            Qipcrtr = AF_QIPCRTR,       // Qualcomm IPC router interface protocol
            Smc = AF_SMC,               // SMC-R (shared memory communications over RDMA) protocol
            Xdp = AF_XDP                // XDP (express data path) interface
        };
        enum class SocketType : int {
            Stream = SOCK_STREAM,       // Provides sequenced, reliable, two-way, connection-based byte streams.
            DGram = SOCK_DGRAM,         // Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
            SeqPacket = SOCK_SEQPACKET, // Provides a sequenced, reliable, two-way connection-based data transmission path for datagrams of fixed maximum length;
            Raw = SOCK_RAW,             // Provides raw network protocol access.
            Rdm = SOCK_RDM              // Provides a reliable datagram layer that does not guarantee ordering.
        };
        enum class Level : int {
            Ip = IPPROTO_IP,      // IPv4
            IpV6 = IPPROTO_IPV6,  // IPv6
            Icmp = IPPROTO_ICMP,  // ICMP
            Raw = IPPROTO_RAW,    // Raw
            Tcp = IPPROTO_TCP,    // TCP
            Udp = IPPROTO_UDP,    // UDP
            Socket = SOL_SOCKET   // Socket api
        };
        enum class Address : int64_t {
            All = INADDR_ANY,            // 0.0.0.0
            Broadcast = INADDR_BROADCAST
        };

        Socket();
        
        bool create();
        bool setSocketOptions();
        bool bind();
        bool listen(const int queueSize = 10);
        int accept();
        bool connect();
        int close(const int connDescriptor);

        std::string read(const int connDescriptor, const int bufferSize = 1024);
        int write(const int connDescriptor, const char *buffer);
        int write(const int connDescriptor, const std::string &buffer);

        void setIp(const std::string &ipL);
        void setIp(const Address ipL);
        void setPort(const int portL);
        void setDomain(const Domain domainL);
        void setSocketType(const SocketType socketTypeL);
        void setSocketType(const int socketTypeL);
        void setProtocol(const int protocolL);
        void setApiLevel(const int apiLevelL);
        void setOptions(const int optionsL);

    private:
        int port = 9300;
        //int bufferSize = 1024;
        //std::vector<char> buffer;
        unsigned int ip = INADDR_ANY;
        int sockfd; // Socket decriptir
        int connfd; // Connection descriptor
        struct sockaddr_in servaddr; // Socket paremeters struct
        socklen_t len; // Sores sizeof() of a servaddr variable
        int opt = 1; // ???
        //struct sockaddr_in cli; // ???

        int domain = AF_INET;
        int socketType = SOCK_STREAM;
        int protocol = 0;
        int apiLevel = SOL_SOCKET;
        int options = SO_REUSEADDR | SO_REUSEPORT;
        int acceptNumb = -1;
    };
}

#endif // KTOOLS_NETWORK_SOCKET_H
