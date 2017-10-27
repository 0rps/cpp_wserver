#include "listener.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <sys/select.h>

#include "httphandler.h"

const int listen_timeout_ms = 1000;
const int const_backlog_size = 100;


#include <fcntl.h>
#include <sys/ioctl.h>

inline bool setNonblock(int _socketFd) {
    int flags;

        /* If they have O_NONBLOCK, use the Posix way to do it */
    #if defined(O_NONBLOCK)
        /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
        if (-1 == (flags = fcntl(_socketFd, F_GETFL, 0)))
            flags = 0;
        return fcntl(_socketFd, F_SETFL, flags | O_NONBLOCK) == 0;
    #else
        /* Otherwise, use the old way of doing it */
        flags = 1;
        return ioctl(_socketFd, FIOBIO, &flags) == 0;
    #endif
}



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
    sin.sin_port = htons(m_paramPort);

    /// struct hostent *info = gethostbyname(m_paramAddr.c_str);
    /// if (info == NULL) { ... }
    /// sin.sin_addr = *(struct in_addr *) info->h_addr;

    //sin.sin_addr = htonl(INADDR_LOOPBACK);
    //sin.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_aton(m_paramAddr.c_str(), &sin.sin_addr);

    std::cout << "real addr: " << m_paramAddr << ", sin addr" << sin.sin_addr.s_addr << " , port = " << sin.sin_port << std::endl;

    int optval = 1;
    if (setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        close(m_listenSocket);
        return false;
    }

    if (false == setNonblock(m_listenSocket)) {
        close(m_listenSocket);
        std::cerr << "SetNonblock failed" << std::endl;
        return false;
    }

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
    return m_isStarted;
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
    return true;
}

int Listener::nextSocket()
{
//    struct sockaddr_in client;
//    int client_size = sizeof(client);
//    int resFd = accept(m_listenSocket, (struct sockaddr*)&client, (socklen_t*)&client_size);

//    char buf[512];
//    int count;

//    count = read(resFd, buf, 512);

//    HttpHandler p_handler;
//    p_handler.addRawData(buf, count);

//    if (p_handler.hasMessages()) {
//        HttpMessage msg = p_handler.messages().at(0);
//        std::cout << "Request: " << msg.getRequest() << std::endl;
//    } else {
//        std::cout << "OLOLOLO" << std::endl;
//    }

    std::cout << "Listener: next socket" << std::endl;

    fd_set set;
    struct timeval timeout;
    timeout.tv_sec = 4;
    timeout.tv_usec = 0;

    FD_ZERO(&set);
    FD_SET(m_listenSocket, &set);

    int res = select(m_listenSocket+1, &set, NULL, NULL, &timeout);

    if (res > 0 && FD_ISSET(m_listenSocket, &set)) {
        struct sockaddr_in client;
        int client_size = sizeof(client);
        int resFd = accept(m_listenSocket, (struct sockaddr*)&client, (socklen_t*)&client_size);
        if (resFd == -1) {
            std::cerr << "Server: Couldn't accept connection" << std::endl;
            return 0;
        }
        std::cout << "!!!!!!Listener: Socket accepted with fd = " << resFd << std::endl;
        return resFd;

    } else if (res < 0)  {
        std::cerr << "Server: Select error " << std::endl;
        return -1;
    } else  {
        std::cout << "Server: Accept timeout" << std::endl;
        return 0;
    }
}
