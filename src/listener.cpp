#include "listener.h"

#include <iostream>

const int listen_timeout_ms = 1000;

Listener::Listener(const std::string &_addr, const int _port, const std::string &_dir):
    m_paramAddr(_addr),
    m_paramDir(_dir),
    m_paramPort(_port)
{

}

Listener::~Listener()
{

}

void Listener::start()
{
    std::cout << "Listener: starting" << std::endl;

    std::cout << "Listener: started" << std::endl;
}

void Listener::shutdown()
{
    std::cout << "Listener: try shutdown" << std::endl;
    if (m_isStarted) {

    }

    std::cout << "Listener: shutdown is successful " << std::endl;
}

int Listener::nextSocket()
{
    std::cout << "Listener: next socket" << std::endl;

    if (false == m_isStarted) {
        return -1;
    }

    return -1;
}
