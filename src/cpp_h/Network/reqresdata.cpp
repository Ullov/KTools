#include "reqresdata.h"

void KTools::Network::ReqResData::setHttpVersion(const HttpVersion &version)
{
    httpVersion = version;
}

KTools::Network::ReqResData::HttpVersion KTools::Network::ReqResData::getHttpVersion()
{
    return httpVersion;
}

const std::string& KTools::Network::ReqResData::getBody()
{
    return body;
}
