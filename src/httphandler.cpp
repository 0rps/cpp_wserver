#include "httphandler.h"

#include <iostream>

#include <string.h>
#include <memory>
#include <memory.h>
#include <regex>
#include <unistd.h>

#include "config.h"

HttpMessage::HttpMessage(const bool isResponse):
    m_isResponse(isResponse)
{

}


HttpMessage::~HttpMessage()
{

}


MessageType HttpMessage::getCode() const
{
    return m_code;
}


std::vector<std::pair<std::string, std::string> > HttpMessage::getHeaders() const
{
    return m_headers;
}


std::string HttpMessage::getBody() const
{
    return m_body;
}

std::string HttpMessage::getRequestPath() const
{
    return m_requestPath;
}

std::string HttpMessage::getRequestParams() const
{
    return m_requestPars;
}


std::string HttpMessage::getRequest() const
{
    return m_request;
}


void HttpMessage::setCode(MessageType _code)
{
    m_code = _code;
}

void HttpMessage::setRequest(const std::string &_request)
{
    m_request = _request;

    auto pos = m_request.find('?');
    if (pos != std::string::npos) {
        m_requestPath = m_request.substr(0, pos);
        m_requestPars = m_request.substr(pos);
    } else {
        m_requestPath = m_request;
        m_requestPars = "";
    }
}


void HttpMessage::setHeader(const std::string &_name, const std::string &_value)
{
    std::pair<std::string, std::string> header(_name, _value);
    m_headers.push_back(header);
}


void HttpMessage::setBody(const std::string &_body)
{
    m_body = _body;
}

std::string HttpMessage::getRawMessage()
{
    const std::string p_delimiter = "\r\n";
    const std::string p_code = std::to_string((int)m_code);
    const std::string p_contentType = "text/html";

    std::string p_reasonPhrase;
    std::string p_contentLength = m_body.length() > 0 ? std::to_string(strlen(m_body.c_str()) - 1) : "0";
    std::string p_body = m_body;


    if (m_code == MT_NotFound) {
        p_reasonPhrase = "Not Found";
    } else if (m_code == MT_ServerError) {
        p_reasonPhrase = "Internal Server Error";
    } else {
        p_reasonPhrase = "OK";
    }

    std::string p_result = std::string(HTTP_HEADER) + " " + p_code + " " + p_reasonPhrase + p_delimiter;
    p_result += "Content-Type: " + p_contentType + p_delimiter;
    p_result += "Content-Length: " + p_contentLength + p_delimiter;
    p_result += p_delimiter + p_body;

    return p_result;
}

HttpHandler::HttpHandler() :
    m_buffer(NULL),  m_size(0), m_maxSize(0)
{
    m_maxSize = 64;
    m_buffer = (char*)malloc(m_maxSize);
}


HttpHandler::~HttpHandler()
{
    free(m_buffer);
}

void HttpHandler::addRawData(const char *_data, const int _size)
{
    int newSize = _size + m_size;
    if (newSize > m_maxSize) {
        m_maxSize = newSize + _size;
        m_buffer = (char*)realloc((void*)m_buffer, m_maxSize);
    }
    memcpy(m_buffer + m_size, _data, _size);
    m_size += _size;
    parseBuffer();
}

bool HttpHandler::hasMessages() const
{
    return m_messages.size();
}


HttpMessage HttpHandler::pop()
{
    HttpMessage msg = m_messages.front();
    m_messages.pop_front();

    return msg;
}

void HttpHandler::parseSimpleRequest(std::string &_request)
{
    HttpMessage msg;
    if (_request.size() > 4) {
        msg.setRequest(_request.substr(4));
    }

    //std::cout << "new message with simple request: '" << msg.getRequest() << "'" << std::endl;
    m_messages.push_back(msg);
}

void HttpHandler::parseFullRequest(std::string &_request)
{
    auto lastSymbol = _request.find("\r\n");
    if (lastSymbol == std::string::npos) {
        lastSymbol = _request.size();
    }

    HttpMessage msg;
    int requestURISize = lastSymbol - 4 - 9;
    msg.setRequest(_request.substr(4, requestURISize));

    m_messages.push_back(msg);
}

void HttpHandler::parseBuffer()
{
    if (m_size > 5) {
        if (memcmp("GET", m_buffer, 3) != 0) {
            return;
        }
    } else {
        return;
    }

    int firstStringSize = -1;
    for (int i = 1; i < m_size; i++) {
        if (m_buffer[i-1] == '\r' && m_buffer[i] == '\n') {
            firstStringSize = i-1;
            break;
        }
    }

    bool isFullRequest = false;
    if (firstStringSize > 9) {
        char httpMarker[] = HTTP_HEADER;
        int httpMarkerSize = sizeof(httpMarker) - 1;
        char *markerPossiblePosition = m_buffer + firstStringSize - httpMarkerSize;
        if (strncmp(markerPossiblePosition, httpMarker, httpMarkerSize) == 0) {
            isFullRequest = true;
        }
    }

    std::string p_firstString(m_size, firstStringSize);
    //std::cout << "First string " << p_firstString << std::endl;

    int cuttedSize = 0;


    if (isFullRequest) {
        int requestLengthWithCRLF = -1;
        const char endMarker[] = "\r\n\r\n";
        int endMarkerSize = sizeof(endMarker) - 1;
        for (int i = firstStringSize; i < m_size; i++) {
            char* httpMarkerStartPointer = m_buffer + i - endMarkerSize +1 ;
            if (strncmp(httpMarkerStartPointer, endMarker, endMarkerSize) == 0) {
                requestLengthWithCRLF = i + 1;
                break;
            }
        }

        if (requestLengthWithCRLF > 0) {
            cuttedSize = requestLengthWithCRLF;
            std::string request(m_buffer, requestLengthWithCRLF - endMarkerSize);
            parseFullRequest(request);
        }

    } else {
        cuttedSize = firstStringSize + 2;
        std::string request(m_buffer, firstStringSize);
        parseSimpleRequest(request);
    }

    if (cuttedSize > 0) {
        if (cuttedSize < m_size) {
            if (m_buffer[cuttedSize] == '\0') {
                cuttedSize++;
            }
        }

        if (cuttedSize == m_size) {
            m_size = 0;
        } else {
            memmove((void*)m_buffer, (void*)(m_buffer+cuttedSize), m_size - cuttedSize);
            m_size -= cuttedSize;
        }
        parseBuffer();
    }
}


FileExtractor::FileExtractor(const std::string &_dir): m_dir(_dir)
{
    if (m_dir.length() > 0) {
        if (m_dir.back() == '/') {
            m_dir.pop_back();
        }
    }
}

const std::string FileExtractor::getFileContent(const std::string &_relpath, int &_error) const
{
    const std::string &p_path = getFullPath(_relpath);
    //std::cout << "FileExtractor: full path = " << p_path << std::endl;
    FILE *file;
    int fileSize;
    char* buf;

    _error = 0;

    file = fopen(p_path.c_str(), "r");

    if (file == NULL) {
        _error = -1;;
        return std::string();
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    buf = (char*)malloc(fileSize*sizeof(char));

    if (buf == NULL) {
        _error = -2;
        fclose(file);
        return std::string();
    }

    int resultSize = fread(buf, sizeof(char), fileSize, file);
    if (resultSize != fileSize) {
        free(buf);
        _error = -2;
        fclose(file);
        return std::string();
    }

    std::string p_result(buf, fileSize);
    fclose(file);
    return p_result;
}

bool FileExtractor::fileExists(const std::string &_relpath) const
{
    return fileExists(_relpath, true);
}

const std::string FileExtractor::getFullPath(const std::string &_relpath) const
{
    std::string p_path = m_dir;
    if (_relpath.front() != '/') {
        p_path.push_back('/');
    }
    p_path += _relpath;

    return p_path;
}

bool FileExtractor::fileExists(const std::string &_path, const bool _isRelative) const
{
    const std::string& p_path = _isRelative ? getFullPath(_path) : _path;

    if (access(p_path.c_str(), R_OK) == -1) {
        return false;
    }

    return true;
}
