#include "httphandler.h"

#include <iostream>

#include <string.h>

#include <regex>

HttpMessage::HttpMessage(const bool isResponse):
    m_isResponse(isResponse)
{

}


HttpMessage::~HttpMessage()
{

}


int HttpMessage::getCode() const
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


std::string HttpMessage::getRequest() const
{
    return m_request;
}


void HttpMessage::setCode(int _code)
{
    m_code = _code;
}

void HttpMessage::setRequest(const std::string &_request)
{
    m_request = _request;
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

char *HttpMessage::getRawMessage()
{
//    if (!m_isResponse) {
//        return NULL;
//    }

    char* ans = "HTTP/1.1 200 \r\nContent-Type: text/html\r\nContent-Length: 37\r\n\r\n<html><body>HELLO WORLD!<body></html>";

    return ans;
}

HttpHandler::HttpHandler() :
    m_buffer(NULL), m_maxSize(0), m_size(0)
{
    m_maxSize = 64;
    m_buffer = (char*)malloc(m_maxSize);
}


HttpHandler::~HttpHandler()
{

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

    std::cout << "new message with simple request: '" << msg.getRequest() << "'" << std::endl;
    m_messages.push_back(msg);
}

void HttpHandler::parseFullRequest(std::string &_request)
{
    int lastSymbol = _request.find("\r\n");
    if (lastSymbol == std::string::npos) {
        lastSymbol = _request.size();
    }

    HttpMessage msg;
    int requestURISize = lastSymbol - 4 - 9;
    msg.setRequest(_request.substr(4, requestURISize));

    std::cout << "new message with full request: '" << msg.getRequest() << "'" << std::endl;

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
        char httpMarker[] = "HTTP/1.1";
        int httpMarkerSize = sizeof(httpMarker) - 1;
        char *markerPossiblePosition = m_buffer + firstStringSize - httpMarkerSize;
        if (strncmp(markerPossiblePosition, httpMarker, httpMarkerSize) == 0) {
            isFullRequest = true;
        }
    }

    std::string p_firstString(m_size, firstStringSize);
    std::cout << "First string " << p_firstString << std::endl;

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
            std::memmove((void*)m_buffer, (void*)(m_buffer+cuttedSize), m_size - cuttedSize);
            m_size -= cuttedSize;
        }
        parseBuffer();
    }
}
