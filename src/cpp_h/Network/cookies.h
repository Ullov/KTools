#ifndef NETWORK_COOKIES_H
#define NETWORK_COOKIES_H

#include <string>
#include <map>

namespace KTools::Network
{
    class Cookies
    {
    public:
        Cookies(){}

        void insert(const std::string &key, const std::string &value);
        std::string& operator[](const std::string &key);

    private:
        std::map<std::string, std::string> cookiesMap;
    };
}

#endif // NETWORK_COOKIES_H
