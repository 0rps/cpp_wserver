#include <vector>
#include <string>

class HttpMessage {
public:
    HttpMessage();
    ~HttpMessage();

    int getCode() const;
    std::vector<std::pair<std::string, std::string>> getHeaders() const;
    std::string getBody() const;
    std::string getRequest() const;

    void setCode(int _code);
    void setHeader(const std::string &_name, const std::string &_value);
    void setBody(const std::string &_body);

    char* getRawMessage();

private:
    int code;
    std::string _headers;
    std::string _body;
    std::vector<std::pair<std::string, std::string>> m_headers;
};

class HttpHandler {
public:
    HttpHandler();
    ~HttpHandler();

    void addRawData(const char* _data, const int _size);

    bool hasMessages() const;
    std::vector<HttpMessage> messages() const;
private:
    std::vector<HttpMessage> m_messages;
    char* m_buffer;
    int m_size;
    int m_maxSize;
};
