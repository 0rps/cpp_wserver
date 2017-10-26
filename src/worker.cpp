#include "worker.h"

#include <iostream>

Worker::Worker(int _number, int _sockFd, char *_shared, const std::string &_dir):
    m_number(_number), m_socketFd(_sockFd), m_sharedMem(_shared), m_isError(false)
{
    lgname = "Worker " + std::to_string(_number) + ": ";
    std::cout << lgname << " constructor" << std::endl;
}

Worker::~Worker()
{
    std::cout << lgname << " destructor" << std::endl;
}

bool Worker::tryToHandle()
{
    return false;
}

bool Worker::isError()
{
    return false;
}
