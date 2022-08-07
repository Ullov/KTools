#include "response.h"

#include "log.h"

void KTools::Network::Response::setResponseCode(const int code)
{
    switch (code)
    {
        case 100: responseCode = "100 Continue"; break;
        case 101: responseCode = "101 Switching Protocols"; break;
        case 200: responseCode = "200 OK"; break;
        case 201: responseCode = "201 Created"; break;
        case 202: responseCode = "202 Accepted"; break;
        case 203: responseCode = "203 Non-Authoritative Information"; break;
        case 204: responseCode = "204 No Content"; break;
        case 205: responseCode = "205 Reset Content"; break;
        case 206: responseCode = "206 Partial Content"; break;
        case 300: responseCode = "300 Multiple Choices"; break;
        case 301: responseCode = "301 Moved Permanently"; break;
        case 302: responseCode = "302 Found"; break;
        case 303: responseCode = "303 See Other"; break;
        case 304: responseCode = "304 Not Modified"; break;
        case 307: responseCode = "307 Temporary Redirect"; break;
        case 308: responseCode = "308 Permanent Redirect"; break;
        case 400: responseCode = "400 Bad Request"; break;
        case 401: responseCode = "401 Unauthorized"; break;
        case 402: responseCode = "402 Payment Required"; break;
        case 403: responseCode = "403 Forbidden"; break;
        case 404: responseCode = "404 Not Found"; break;
        case 405: responseCode = "405 Method Not Allowed"; break;
        case 406: responseCode = "406 Not Acceptable"; break;
        case 407: responseCode = "407 Proxy Authentication Required"; break;
        case 408: responseCode = "408 Request Timeout"; break;
        case 409: responseCode = "409 Conflict"; break;
        case 410: responseCode = "410 Gone"; break;
        case 411: responseCode = "411 Length Required"; break;
        case 412: responseCode = "412 Precondition Failed"; break;
        case 413: responseCode = "413 Content Too Large"; break;
        case 414: responseCode = "414 URI Too Long"; break;
        case 415: responseCode = "415 Unsupported Media Type"; break;
        case 416: responseCode = "416 Range Not Satisfiable"; break;
        case 417: responseCode = "417 Expectation Failed"; break;
        case 418: responseCode = "418 I'm a teapot"; break; // 1st April joke
        case 421: responseCode = "421 Misdirected Request"; break;
        case 422: responseCode = "422 Unprocessable Content"; break;
        case 426: responseCode = "426 Upgrade Required"; break;
        case 500: responseCode = "500 Internal Server Error"; break;
        case 501: responseCode = "501 Not Implemented"; break;
        case 502: responseCode = "502 Bad Gateway"; break;
        case 503: responseCode = "503 Service Unavailable"; break;
        case 504: responseCode = "504 Gateway Timeout"; break;
        case 505: responseCode = "505 HTTP Version Not Supported"; break;
        default: KLOG_ERROR("Attempt set unknown response status code: " + QString::number(code));
    }
}

template <>
const int& KTools::Network::Response::getResponseCode()
{
    return numericResponseCode;
}

template <>
const std::string& KTools::Network::Response::getResponseCode()
{
    return responseCode;
}
