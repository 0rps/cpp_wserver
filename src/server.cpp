#include "server.h"

#include <iostream>

#include "listener.h"

Server::Server(int *_shared):
    m_sharedMemory(_shared)

{
    std::cout << "Server: constructor" << std::endl;
}


Server::~Server()
{
    std::cout << "Server: desctructor" << std::endl;
}

void Server::addWorker(const int _number, const int _pid, const int _socket)
{
    WorkerData p_data {_pid, _socket};
    m_workers.insert(std::pair<int, WorkerData>(_number, p_data));
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
    /// TODO: implement
    return false;
}
