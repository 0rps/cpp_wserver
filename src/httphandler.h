#include <vector>
#include <string>
#include <list>

class FileExtractor {
public:
    FileExtractor(const std::string &_dir);

    const std::string getFileContent(const std::string &_relpath, int &_error) const;
    bool fileExists(const std::string &_relpath) const;

private:
    const std::string getFullPath(const std::string &_relpath) const;
    bool fileExists(const std::string &_path, const bool _isRelative) const;

private:
    std::string m_dir;
};

enum MessageType  {
    MT_OK = 200,
    MT_NotFound = 404,
    MT_ServerError = 500
};

class HttpMessage {
public:
    HttpMessage(const bool isResponse = false);
    ~HttpMessage();

    MessageType getCode() const;
    std::vector<std::pair<std::string, std::string>> getHeaders() const;
    std::string getBody() const;
    std::string getRequestPath() const;
    std::string getRequestParams() const;
    std::string getRequest() const;

    void setCode(MessageType _code);
    void setRequest(const std::string &_request);
    void setHeader(const std::string &_name, const std::string &_value);
    void setBody(const std::string &_body);

    std::string getRawMessage();

private:
    bool m_isResponse;
    MessageType m_code;
    std::string m_request;
    std::string m_requestPars;
    std::string m_requestPath;
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

    bool hasRawData() const { return m_size > 0; }

private:
    void parseSimpleRequest(std::string &_request);
    void parseFullRequest(std::string &_request);
    void parseBuffer();

private:
    std::list<HttpMessage> m_messages;
    char* m_buffer;
    int m_size;
    int m_maxSize;
};
