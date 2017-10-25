#include <list>

class TaskScheduler {
public:
    TaskScheduler(const std::list<int> &_workersPIds);
    ~TaskScheduler();

    void sendSocket(const int fd);

private:
    std::list<int> m_workerPIds;
};
