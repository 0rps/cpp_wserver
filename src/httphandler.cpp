#include "httphandler.h"

HttpMessage::HttpMessage()
{

}


HttpMessage::~HttpMessage()
{

}


int HttpMessage::getCode() const
{

}


std::vector<std::pair<std::string, std::string> > HttpMessage::getHeaders() const
{

}


std::string HttpMessage::getBody() const
{

}


std::string HttpMessage::getRequest() const
{

}


void HttpMessage::setCode(int _code)
{

}


void HttpMessage::setHeader(const std::string &_name, const std::string &_value)
{

}


void HttpMessage::setBody(const std::string &_body)
{

}


char *HttpMessage::getRawMessage()
{

}


void HttpHandler::addRawData(const char *_data, const int _size)
{

}


HttpHandler::HttpHandler()
{

}


HttpHandler::~HttpHandler()
{

}


bool HttpHandler::hasMessages() const
{
    return m_messages.size();
}


std::vector<HttpMessage> HttpHandler::messages() const
{
    return m_messages;
}
