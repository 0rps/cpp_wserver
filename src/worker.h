#include <string>

class Worker {
public:
    Worker(int _number, int _sockFd, char* _shared, const std::string &_dir);
    ~Worker();

    bool tryToHandle();
    bool isError();

private:
    int m_number;
    int m_socketFd;

    char* m_sharedMem;

    bool m_isError;

    std::string lgname;
};
