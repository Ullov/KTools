#include "cookies.h"

void KTools::Network::Cookies::insert(const std::string &key, const std::string &value)
{
    cookiesMap.insert({key, value});
}

std::string& KTools::Network::Cookies::operator[](const std::string &key)
{
    return cookiesMap[key];
}
