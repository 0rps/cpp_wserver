#include <string>

class Listener {
public:
    Listener(const std::string &_addr, const int _port, const std::string &_dir);
    ~Listener();

    void start();
    void shutdown();

    int nextSocket();

private:
    std::string m_paramAddr;
    std::string m_paramDir;
    int m_paramPort;

    bool m_isStarted;
};
