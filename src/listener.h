#include <string>

class Listener {
public:
    Listener(const std::string &_addr, const int _port);
    ~Listener();

    bool start();
    bool shutdown();

    int nextSocket();

private:
    std::string m_paramAddr;
    int m_paramPort;

    bool m_isStarted;

    int m_listenSocket;

};
