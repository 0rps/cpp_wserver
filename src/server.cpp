#include "server.h"

#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#include "listener.h"

Server::Server(int *_shared):
    m_sharedMemory(_shared), next(-1)

{
    std::cout << "Server: constructor" << std::endl;
}


Server::~Server()
{
    std::cout << "Server: destructor" << std::endl;
}

void Server::addWorker(const int _number, const int _pid, const int _socket)
{
    WorkerData p_data {_pid, _socket};
    m_workers.insert(std::pair<int, WorkerData>(_number, p_data));
}

bool Server::scheduleNewClient(const int _socketFd)
{
    bool flag = false;
    for (size_t i = 0; i < m_workers.size(); i++) {
        if (m_sharedMemory[i] == 0) {
            m_sharedMemory[i] = 1;
            std::cout << "Server: soft sending to " << i << " worker" << std::endl;
            if (sendToWorker(_socketFd, i)) {
                flag = true;
                break;
            } else {
                std::cout << "Server: soft sending to " << i << " worker failed" << std::endl;
            }
        }
    }

    int size = m_workers.size();

    if (!flag) {
        while (size > 0) {
            next++;
            next = next % m_workers.size();
            std::cout << "Server: hard sending to " << next << " worker" << std::endl;
            m_sharedMemory[next] = 1;
            if (sendToWorker(_socketFd, next)) {
                break;
            } else {
                std::cout << "Server: hard sending to " << next << " worker failed" << std::endl;
            }
            size--;
        }
        if (size == 0) {
            return false;
        }
    }

    return true;
}

void Server::validateChildProcesses()
{
    /// TODO: check
    std::cout << "Server: validate child processes" << std::endl;
}

int Server::getWorkersCount() const
{
    std::cout << "Server: get workers count: " << m_workers.size() << std::endl;
    return m_workers.size();
}

bool Server::sendToWorker(const int _fd, const int _workerIndex)
{
    std::cout << "Server: try to send socket to " << _workerIndex << " worker " << std::endl;

    WorkerData p_worker = m_workers[_workerIndex];

    struct msghdr msgh;
    struct iovec iov;
    int data;

    union {
        struct cmsghdr cmh;
        char   control[CMSG_SPACE(sizeof(int))];
                        /* Space large enough to hold an 'int' */
    } control_un;
    struct cmsghdr *cmhp;

    msgh.msg_iov = &iov;
    msgh.msg_iovlen = 1;
    iov.iov_base = &data;
    iov.iov_len = sizeof(int);
    data = 12345;

    msgh.msg_name = NULL;
    msgh.msg_namelen = 0;

    msgh.msg_control = control_un.control;
    msgh.msg_controllen = sizeof(control_un.control);

    cmhp = CMSG_FIRSTHDR(&msgh);
    cmhp->cmsg_len = CMSG_LEN(sizeof(int));
    cmhp->cmsg_level = SOL_SOCKET;
    cmhp->cmsg_type = SCM_RIGHTS;
    *((int *) CMSG_DATA(cmhp)) = _fd;

    int sendRes = sendmsg(p_worker.socketFd, &msgh, 0);
    if (sendRes == -1) {
        std::cout << "Server: sending socket to" << _workerIndex << " failed " << std::endl;
    } else {
        std::cout << "Server: sending socket to" << _workerIndex << " is successful " << std::endl;

    }

    return sendRes != -1;

}
