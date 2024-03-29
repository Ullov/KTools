#ifndef KTOOLS_NETWORK_REQUEST_H
#define KTOOLS_NETWORK_REQUEST_H

#include "reqresdata.h"
#include "cookies.h"

namespace KTools::Network
{
    class Request : public ReqResData
    {
    public:
        Request(const std::string &rawData);

        enum class Type
        {
            GET,
            POST,
            HEAD,
            PUT,
            DELETE,
            PRI
        };

        Cookies cookies;

        const std::string& getPath();
        const Type& getType();
        void setHttpVersion(const std::string &value);
        const std::string& getPostParam(const std::string &key);
        const std::string& getGetParam(const std::string &key);
    private:
        Type type;
        std::string path;
        std::string raw;
        std::string body;
        std::map<std::string, std::string> postParams;
        std::map<std::string, std::string> getParams;

        void setType(const std::string &value);
        void setBody(const std::string &data);
        void setPath(const std::string &value);

        std::map<std::string, std::string> urlencodedToMap(const std::string &encoded);

        using ReqResData::setHttpVersion;
    };
}

#endif // KTOOLS_NETWORK_REQUEST_H
