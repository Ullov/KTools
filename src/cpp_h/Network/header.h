#ifndef NETWORK_HEADER_H
#define NETWORK_HEADER_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace KTools::Network
{
    class Header
    {
    public:
        Header(){}

        enum class SameSite
        {
            Strict,
            Lax,
            None
        };

        void insert(const std::string &key, const std::string &value);
        void insert(const std::string &fullLine);
        std::string& operator[](const std::string &key);
        std::string toString();
        void erase(std::map<std::string, std::string>::iterator i);
        std::map<std::string, std::string>::iterator begin();
        std::map<std::string, std::string>::iterator end();
        std::map<std::string, std::string>::iterator find(const std::string &key);
        void setCookie(const std::string &key, const std::string &value, const std::time_t expires = 0, const int maxAge = -1, const std::string &domain = "", const std::string &path = "/", bool secure = false, const bool httpOnly = false, const SameSite sameSite = SameSite::Lax);
        void fromRawString(const std::string &raw);

    private:
        std::map<std::string, std::string> headerMap;
        std::vector<std::string> setCookieLines;
    };
}

#endif // NETWORK_HEADER_H
