#include "httphandler.h"

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
    /// TODO:
}

HttpHandler::HttpHandler() :
    m_buffer(NULL), m_maxSize(0), m_size(0)
{
    m_maxSize = 256;
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


}

bool HttpHandler::hasMessages() const
{
    return m_messages.size();
}

std::vector<HttpMessage> HttpHandler::messages() const
{
    return m_messages;
}

bool HttpHandler::parseMessage(int _end)
{
    std::string request(m_buffer);

    if (_end == m_size-1) {
        m_size = 0;
    } else {
        memmove((void*)(m_buffer+_end+1), (void*)m_buffer, (m_size-1-_end));
        m_size = m_size-1-_end;
    }

}

void HttpHandler::parseBuffer()
{
    if (m_size > 3) {
        if (memcmp("GET", m_buffer, 3) != 0) {
            return;
        }
    }

    int end = -1;
    for (int i = 2; i < m_size; i++) {
        if (m_buffer[i] == '\0' && m_buffer[i-1] == '\n' && m_buffer[i-2] == '\n') {
            end = i;
            break;
        }
    }

    if (end > 0) {
        parseMessage(end);
        parseBuffer();
    }
}
