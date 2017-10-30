#include <string>

class Worker {
public:
    Worker(int _number, int _sockFd, int* _shared, const std::string &_dir);
    ~Worker();

    int waitClientSocket();
    bool tryToHandle(int _clientSocket);
    bool isError();

private:
    int m_number;
    int m_socketToParentFd;

    int* m_sharedMem;

    std::string m_dir;

    bool m_isError;

    std::string lgname;
};
