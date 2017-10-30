#include <map>

struct WorkerData {
    int pid;
    int socketFd;
};

class Server {
public:
    Server(int* _shared);

    ~Server();
    void addWorker(const int _number, const int _pid, const int _socket);
    bool scheduleNewClient(const int _socketFd);

    void validateChildProcesses();
    int  getWorkersCount() const;

private:
    bool sendToWorker(const int _fd, const int _workerIndex);

private:
    int* m_sharedMemory;
    int next;
    std::map<int, WorkerData> m_workers;
};
