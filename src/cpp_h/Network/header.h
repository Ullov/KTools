#ifndef NETWORK_HEADER_H
#define NETWORK_HEADER_H

#include <string>
#include <map>

namespace KTools::Network
{
    class Header
    {
    public:
        Header(){}

        void insert(const std::string &key, const std::string &value);
        void insert(const std::string &fullLine);
        std::string& operator[](const std::string &key);
        std::string toString();
        void erase(std::map<std::string, std::string>::iterator i);
        std::map<std::string, std::string>::iterator begin();
        std::map<std::string, std::string>::iterator end();
        std::map<std::string, std::string>::iterator find(const std::string &key);

    private:
        std::map<std::string, std::string> headerMap;
    };
}

#endif // NETWORK_HEADER_H
