#include "reqresdata.h"

void KTools::Network::ReqResData::setHttpVersion(const HttpVersion &version)
{
    httpVersion = version;
}

template <>
KTools::Network::ReqResData::HttpVersion KTools::Network::ReqResData::getHttpVersion()
{
    return httpVersion;
}

template <>
std::string KTools::Network::ReqResData::getHttpVersion()
{
    if (httpVersion == HttpVersion::HTTP11)
        return "HTTP/1.1";
    else if (httpVersion == HttpVersion::HTTP10)
        return "HTTP/1.0";
    else if (httpVersion == HttpVersion::HTTP09)
        return "HTTP/0.9";
    else
        return "HTTP/1.1";
}

const std::string& KTools::Network::ReqResData::getBody()
{
    return body;
}
