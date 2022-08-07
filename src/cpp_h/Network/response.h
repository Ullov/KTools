#ifndef KTOOLS_NETWORK_RESPONSE_H
#define KTOOLS_NETWORK_RESPONSE_H

#include "reqresdata.h"

namespace KTools::Network
{
    class Response : public ReqResData
    {
    public:
        Response() {}

        void setResponseCode(const int code);
        template <typename T>
        const T& getResponseCode();
        void write(const std::string &data);
        std::string toString();
    private:
        std::string responseCode = "200 OK";
        int numericResponseCode = 200;
    };
}

#endif // KTOOLS_NETWORK_RESPONSE_H
