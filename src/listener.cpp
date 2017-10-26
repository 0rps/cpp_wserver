#include "listener.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <sys/select.h>

const int listen_timeout_ms = 1000;
const int const_backlog_size = 100;

Listener::Listener(const std::string &_addr, const int _port):
    m_paramAddr(_addr),
    m_paramPort(_port)
{

}

Listener::~Listener()
{

}

bool Listener::start()
{
    std::cout << "Listener: starting" << std::endl;

    m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_listenSocket == -1) {
        std::cerr << "Couldn't create listen socket" << std::endl;
        return false;
    }

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = m_paramPort;

    /// struct hostent *info = gethostbyname(m_paramAddr.c_str);
    /// if (info == NULL) { ... }
    /// sin.sin_addr = *(struct in_addr *) info->h_addr;

    //sin.sin_addr = htonl(INADDR_LOOPBACK);
    inet_aton("127.0.0.1", &sin.sin_addr);

    if (bind(m_listenSocket, (struct sockaddr*)&sin, sizeof(sockaddr_in)) == -1) {
        std::cerr << "Couldn't bind listen socket" << std::endl;
        close(m_listenSocket);
        return false;
    }

    if (listen(m_listenSocket, const_backlog_size) == -1) {
        std::cerr << "Couldn't operate listen function" << std::endl;
        close(m_listenSocket);
        return false;
    }

    m_isStarted = true;

    std::cout << "Listener: started" << std::endl;
}

bool Listener::shutdown()
{
    std::cout << "Listener: try shutdown" << std::endl;
    if (m_isStarted) {
        /// check and handle errors
        ::shutdown(m_listenSocket, SHUT_RDWR);
        close(m_listenSocket);
    }

    std::cout << "Listener: shutdown is successful " << std::endl;
}

int Listener::nextSocket()
{
    std::cout << "Listener: next socket" << std::endl;

    fd_set set;
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    FD_ZERO(&set);
    FD_SET(m_listenSocket, &set);

    int res = select(1, &set, NULL, NULL, &timeout);

    if (res > 0) {
        struct sockaddr_in client;
        int client_size = sizeof(client);
        int resFd = accept(m_listenSocket, (struct sockaddr*)&client, (socklen_t*)&client_size);
        if (resFd == -1) {
            std::cerr << "Server: Couldn't accept connection" << std::endl;
            return 0;
        }
        return resFd;
    } else if (res == 0) {
        std::cout << "Server: Accept timeout" << std::endl;
        return 0;
    }

    /// else
    std::cerr << "Server: Select error " << std::endl;
    return -1;

}
