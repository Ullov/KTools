#ifndef KTOOLS_NETWORK_REQ_RES_DATA_H
#define KTOOLS_NETWORK_REQ_RES_DATA_H

#include "header.h"

namespace KTools::Network
{
    class ReqResData
    {
    public:
        ReqResData() {}

        enum class HttpVersion
        {
            HTTP09,
            HTTP10,
            HTTP11
        };
        Header header;

        void setHttpVersion(const HttpVersion &version);
        template <typename T>
        T getHttpVersion();
        const std::string& getBody();
    protected:
        HttpVersion httpVersion = HttpVersion::HTTP11;
        std::string body;
    };
}

#endif // KTOOLS_NETWORK_REQ_RES_DATA_H