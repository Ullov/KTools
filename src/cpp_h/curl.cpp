#include "curl.h"

#include "file.h"
#include "log.h"

KTools::Curl::Curl()
{
    if (!KTools::File::fileExist(fullCacertPath))
        KTools::File::copyFile(pathToCacertInQrc, cacertPath, cacertFileName);
    handlesList = new QVector<CurlHandle*>({new CurlHandle()});
    numb = 0;
}

KTools::Curl::~Curl()
{
    QVector<CurlHandle*>::iterator end = handlesList->end();
    for (QVector<CurlHandle*>::iterator i = handlesList->begin(); i != end; ++i)
        delete (*i);

    delete handlesList;
}

quint64 KTools::Curl::writeMemoryCallback(char *data, quint64 size, quint64 nmemb, QByteArray *writerData)
{
    if (writerData == NULL)
        return 0;
    writerData->append(data, size*nmemb);
    return size * nmemb;
}

void KTools::Curl::setHeader(QVector<QByteArray> chunk, const SetHeaderMode mode)
{
    curl_slist_free_all(handlesList->at(numb)->slistHeader);
    handlesList->at(numb)->slistHeader = NULL;
    for (qint64 i = 0; i < chunk.size(); i++)
    {
        handlesList->at(numb)->slistHeader = curl_slist_append(handlesList->at(numb)->slistHeader, chunk[i]);
    }
}

QByteArray KTools::Curl::request(const QString &url)
{
    QByteArray buffer;
    std::string stdPostParam = handlesList->at(numb)->postParam->toStdString();
    std::string stdUrl = url.toStdString();

    curlEasySetopt(CURLOPT_URL, stdUrl);
    curlEasySetopt(CURLOPT_WRITEDATA, buffer);

    if (handlesList->at(numb)->requestType == RequestType::Post)
    {
        curlEasySetopt(CURLOPT_POSTFIELDS, stdPostParam);
        curlEasySetopt(CURLOPT_POSTFIELDSIZE, stdPostParam.size());
    }

    handlesList->at(numb)->res = curl_easy_perform(handlesList->at(numb)->handle);

    if (handlesList->at(numb)->res != CURLE_OK)
    {
        KTools::Log::writeError("Error in request. URL: " + url, "CurlClass");
        return "Error in CURL";
    }
    else
    {
        return buffer;
    }
}

void KTools::Curl::restartSession()
{
    curl_easy_cleanup(handlesList->at(numb)->handle);
    handlesList->at(numb)->handle = curl_easy_init();
}

quint64 KTools::Curl::headerCallback(char *buffer, quint64 size, quint64 nitems, QByteArray *userdata)
{
    userdata->append(buffer, nitems * size);
    return nitems * size;
}

void KTools::Curl::setOptions()
{
    curl_easy_setopt(handlesList->at(numb)->handle, CURLOPT_WRITEFUNCTION, writeMemoryCallback); // send all data to this function
    curlEasySetopt(CURLOPT_ACCEPT_ENCODING, acceptEncoding);
    curlEasySetopt(CURLOPT_FOLLOWLOCATION, 1L);
    curlEasySetopt(CURLOPT_MAXREDIRS, 5L);
    curlEasySetopt(CURLOPT_USERAGENT, userAgent);

    setHttpVersion(handlesList->at(numb)->httpVersion);
    setRequestType(handlesList->at(numb)->requestType);
    setCookieMode(handlesList->at(numb)->cookieMode);
    setHeaderMode(handlesList->at(numb)->headerMode);
    setAutoReferer(handlesList->at(numb)->autoRefer);
    setVerifyPeer(handlesList->at(numb)->verifyPeer);
    setCaCertPath(handlesList->at(numb)->caCertPath);
    setCaCertMode(handlesList->at(numb)->caCertMode);
}

void KTools::Curl::setRequestType(RequestType requType)
{
    handlesList->at(numb)->requestType = requType;
    if (requType == RequestType::Get)
    {
        curlEasySetopt(CURLOPT_CUSTOMREQUEST, requestTypesStrings.get);
    }
    else if (requType == RequestType::Post)
    {
        curlEasySetopt(CURLOPT_CUSTOMREQUEST, requestTypesStrings.post);
    }
}

void KTools::Curl::generateHeader()
{
    if (handlesList->at(numb)->slistHeader != NULL)
        curl_slist_free_all(handlesList->at(numb)->slistHeader);

    QMap<QString, QString>::iterator end = handlesList->at(numb)->requestHeader->end();
    for (QMap<QString, QString>::iterator i = handlesList->at(numb)->requestHeader->begin(); i != end; ++i)
    {
        handlesList->at(numb)->slistHeader = curl_slist_append(handlesList->at(numb)->slistHeader, (i.key() + ": " + i.value()).toStdString().c_str());
    }
}

void KTools::Curl::setHeader(const QMap<QString, QString> &chunk)
{
    QMap<QString, QString>::const_iterator end = chunk.end();
    for (QMap<QString, QString>::const_iterator i = chunk.begin(); i != end; ++i)
    {
        handlesList->at(numb)->requestHeader->operator[](i.key()) = i.value();
    }
    generateHeader();
}

void KTools::Curl::setHeaderLine(const std::pair<QString, QString> &headerLine)
{
    handlesList->at(numb)->requestHeader->operator[](headerLine.first) = headerLine.second;
    generateHeader();
}

void KTools::Curl::delHeaderLine(const QString &key)
{
    handlesList->at(numb)->requestHeader->remove(key);
    generateHeader();
}

void KTools::Curl::setErrFile(const QString &path, const QString &fileName)
{
    if (handlesList->at(numb)->stdErr != NULL)
    {
        fclose(handlesList->at(numb)->stdErr);
        handlesList->at(numb)->stdErr = NULL;
    }
    handlesList->at(numb)->stdErr = fopen((path + "/" + fileName).toStdString().c_str(), "w");
    curlEasySetopt(CURLOPT_VERBOSE, 1L);
    curlEasySetopt(CURLOPT_STDERR, handlesList->at(numb)->stdErr);
}

void KTools::Curl::unsetErrFile()
{
    if (handlesList->at(numb)->stdErr != NULL)
    {
        fclose(handlesList->at(numb)->stdErr);
        handlesList->at(numb)->stdErr = NULL;
    }
    curlEasySetopt(CURLOPT_VERBOSE, 0L);
}

void KTools::Curl::addHandle()
{
    handlesList->append(new CurlHandle());
}

void KTools::Curl::swichHandle(const qint32 handleNumber)
{
    numb = handleNumber;
}

void KTools::Curl::setHttpVersion(const HttpVersion vers)
{
    handlesList->at(numb)->httpVersion = vers;
    if (handlesList->at(numb)->httpVersion == HttpVersion::Http2)
    {
        curlEasySetopt(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    }
}

void KTools::Curl::setCookieMode(const CookieMode mode)
{
    handlesList->at(numb)->cookieMode = mode;
    std::string stdPathToCookie = (cookiePath + handlesList->at(numb)->cookieFileName).toStdString();
    if (handlesList->at(numb)->cookieMode == CookieMode::GetAndKeep) // Get cookie in first request and use it in next requests
    {
        curlEasySetopt(CURLOPT_COOKIEJAR, stdPathToCookie);
        handlesList->at(numb)->cookieMode = CookieMode::Keep;
    }
    else if (handlesList->at(numb)->cookieMode == CookieMode::Keep) // Use cookie from file
    {
        curlEasySetopt(CURLOPT_COOKIEFILE, stdPathToCookie);
    }
    else if (handlesList->at(numb)->cookieMode == CookieMode::GetAllTimes) // Get new cookie in each request
    {
        curlEasySetopt(CURLOPT_COOKIEJAR, stdPathToCookie);
        curlEasySetopt(CURLOPT_COOKIEFILE, stdPathToCookie);
    }
    else if (handlesList->at(numb)->cookieMode == CookieMode::Void) // Only starts cookie engine
    {
        curlEasySetopt(CURLOPT_COOKIEFILE, voidString);
    }
}

void KTools::Curl::setHeaderMode(const HeaderMode mode)
{
    handlesList->at(numb)->headerMode = mode;
    if (handlesList->at(numb)->headerMode == HeaderMode::Custom) // Sets header
    {
        curlEasySetopt(CURLOPT_HTTPHEADER, handlesList->at(numb)->slistHeader);
    }
    else if (handlesList->at(numb)->headerMode == HeaderMode::None)
    {
        curlEasySetopt(CURLOPT_HTTPHEADER, nullptr);
    }
}

void KTools::Curl::setAutoReferer(const bool ref)
{
    handlesList->at(numb)->autoRefer = ref;
    if (handlesList->at(numb)->autoRefer)
    {
        curlEasySetopt(CURLOPT_AUTOREFERER, 1L);
    }
    else
    {
        curlEasySetopt(CURLOPT_AUTOREFERER, 0L);
    }
}

void KTools::Curl::setPostParam(const QString &data)
{
    handlesList->at(numb)->postParam->clear();
    handlesList->at(numb)->postParam->append(data);
}

const QString& KTools::Curl::getPostParam()
{
    return *handlesList->at(numb)->postParam;
}

void KTools::Curl::setDebugFile(const QByteArray &path)
{
    handlesList->at(numb)->debugPath = path.toStdString();
    curl_easy_setopt(handlesList->at(numb)->handle, CURLOPT_DEBUGFUNCTION, debugCallback);
    curlEasySetopt(CURLOPT_DEBUGDATA, handlesList->at(numb)->debugPath);
    curlEasySetopt(CURLOPT_VERBOSE, 1L);
}

int KTools::Curl::debugCallback(CURL *handle, curl_infotype type, char *data, quint64 size, const char *userptr)
{
    QByteArray normData;
    normData += QByteArray(data, size);
    if (type == CURLINFO_TEXT)
        KTools::File::writeFile(normData, userptr, "text.txt", QIODevice::Append);
    else if (type == CURLINFO_HEADER_IN)
        KTools::File::writeFile(normData, userptr, "headerIn.txt", QIODevice::Append);
    else if (type == CURLINFO_HEADER_OUT)
        KTools::File::writeFile(normData, userptr, "headerOut.txt", QIODevice::Append);
    else if (type == CURLINFO_DATA_IN)
        KTools::File::writeFile(normData, userptr, "dataIn.txt", QIODevice::Append);
    else if (type == CURLINFO_DATA_OUT)
        KTools::File::writeFile(normData, userptr, "dataOut.txt", QIODevice::Append);
    else if (type == CURLINFO_SSL_DATA_IN)
        KTools::File::writeFile(normData, userptr, "sslDataIn.txt", QIODevice::Append);
    else if (type == CURLINFO_SSL_DATA_OUT)
        KTools::File::writeFile(normData, userptr, "sslDataOut.txt", QIODevice::Append);
    else if (type == CURLINFO_END)
        KTools::File::writeFile(normData, userptr, "end.txt", QIODevice::Append);

    return 0;
}

void KTools::Curl::setVerifyPeer(const bool mode)
{
    handlesList->at(numb)->verifyPeer = mode;
    if (mode)
        curlEasySetopt(CURLOPT_PROXY_SSL_VERIFYPEER, 1L);
    else
        curlEasySetopt(CURLOPT_PROXY_SSL_VERIFYPEER, 0L);
}

void KTools::Curl::setCaCertMode(const CaCertMode mode)
{
    handlesList->at(numb)->caCertMode = mode;
    if (mode == CaCertMode::CustomPath)
        curlEasySetopt(CURLOPT_CAINFO, handlesList->at(numb)->caCertPath);
}

void KTools::Curl::setCaCertPath(const std::string &path)
{
    handlesList->at(numb)->caCertPath = path;
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, std::string &parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, parameter.c_str()) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: " + parameter.c_str());
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, long parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, parameter) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: " + QString::number(parameter));
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, QByteArray &parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, &parameter) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: " + parameter);
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, std::nullptr_t parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, parameter) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: nullptr");
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, curl_slist *parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, parameter) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: curl_slist*");
}

void KTools::Curl::curlEasySetopt(const CURLoption &option, FILE *parameter)
{
    if (curl_easy_setopt(handlesList->at(numb)->handle, option, parameter) != CURLE_OK)
        KLOG_ERROR("Something went wrong. numb: " + QString::number(numb) + "; option: " + QString::number(option) + "; parameter: FILE*");
}
