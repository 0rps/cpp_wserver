#include <vector>
#include <string>

class HttpMessage {
public:
    HttpMessage(const bool isResponse = false);
    ~HttpMessage();

    int getCode() const;
    std::vector<std::pair<std::string, std::string>> getHeaders() const;
    std::string getBody() const;
    std::string getRequest() const;

    void setCode(int _code);
    void setRequest(const std::string &_request);
    void setHeader(const std::string &_name, const std::string &_value);
    void setBody(const std::string &_body);

    char* getRawMessage();

private:
    bool m_isResponse;
    int m_code;
    std::string m_request;
    std::string m_body;
    std::vector< std::pair<std::string, std::string> > m_headers;
};

class HttpHandler {
public:
    HttpHandler();
    ~HttpHandler();

    void addRawData(const char* _data, const int _size);

    bool hasMessages() const;
    HttpMessage pop();
    std::vector<HttpMessage> messages() const;

private:
    void parseSimpleRequest(std::string &_request);
    void parseFullRequest(std::string &_request);
    void parseBuffer();

private:
    std::vector<HttpMessage> m_messages;
    char* m_buffer;
    int m_size;
    int m_maxSize;
};
