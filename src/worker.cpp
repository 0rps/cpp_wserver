#include "worker.h"

#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <string.h>

#include "httphandler.h"


Worker::Worker(int _number, int _sockFd, int *_shared, const std::string &_dir):
    m_number(_number), m_socketToParentFd(_sockFd), m_sharedMem(_shared), m_dir(_dir), m_isError(false)
{
    lgname = "Worker " + std::to_string(_number) + ": ";
    std::cout << lgname << " constructor" << std::endl;
}

Worker::~Worker()
{
    std::cout << lgname << " destructor" << std::endl;
}

int Worker::waitClientSocket()
{
    std::cout << lgname << "Try to receive client socket " << std::endl;

    struct msghdr msgh;
    struct iovec iov;
    int data, fd;
    ssize_t nr;

    /* Allocate a char array of suitable size to hold the ancillary data.
       However, since this buffer is in reality a 'struct cmsghdr', use a
       union to ensure that it is aligned as required for that structure. */
    union {
        struct cmsghdr cmh;
        char   control[CMSG_SPACE(sizeof(int))];
                        /* Space large enough to hold an 'int' */
    } control_un;
    struct cmsghdr *cmhp;

    /* Set 'control_un' to describe ancillary data that we want to receive */

    control_un.cmh.cmsg_len = CMSG_LEN(sizeof(int));
    control_un.cmh.cmsg_level = SOL_SOCKET;
    control_un.cmh.cmsg_type = SCM_RIGHTS;

    /* Set 'msgh' fields to describe 'control_un' */

    msgh.msg_control = control_un.control;
    msgh.msg_controllen = sizeof(control_un.control);

    /* Set fields of 'msgh' to point to buffer used to receive (real)
       data read by recvmsg() */

    msgh.msg_iov = &iov;
    msgh.msg_iovlen = 1;
    iov.iov_base = &data;
    iov.iov_len = sizeof(int);

    msgh.msg_name = NULL;               /* We don't need address of peer */
    msgh.msg_namelen = 0;

    nr = recvmsg(m_socketToParentFd, &msgh, 0);
    if (nr == -1) {
        if (errno == EAGAIN) {
            return 0;
        }
        return -1;
    }

    cmhp = CMSG_FIRSTHDR(&msgh);
    if (cmhp == NULL || cmhp->cmsg_len != CMSG_LEN(sizeof(int)))
        return -1;
    if (cmhp->cmsg_level != SOL_SOCKET)
        return -1;
    if (cmhp->cmsg_type != SCM_RIGHTS)
        return -1;

    fd = *((int *) CMSG_DATA(cmhp));

    std::cout << lgname << "socket is received" << std::endl;

    return fd;
}

bool Worker::tryToHandle(int _clientSocket)
{
    *m_sharedMem = 1;

    char buffer[72];
    const int bufferSize = sizeof(buffer);

    FileExtractor p_fileExtractor(m_dir);
    HttpHandler p_handler;

    while(true) {
        int count = read(_clientSocket, buffer, bufferSize);
        if (count <= 0) {
            close(_clientSocket);
            break;
        }

        p_handler.addRawData(buffer, count);

        while(p_handler.hasMessages()) {
            HttpMessage httpMsg = p_handler.pop();
            std::string relPath = httpMsg.getRequest();

            HttpMessage httpResponseMsg(true);

            if (p_fileExtractor.fileExists(relPath)) {
                int contentErr;
                std::string content = p_fileExtractor.getFileContent(relPath, contentErr);
                if (contentErr >= 0 ) {
                    httpResponseMsg.setCode(MT_OK);
                    httpResponseMsg.setBody(content);
                } else if (contentErr == -1) {
                    httpResponseMsg.setCode(MT_NotFound);
                } else if (contentErr == -2) {
                    httpResponseMsg.setCode(MT_ServerError);
                }
            } else {
                httpResponseMsg.setCode(MT_NotFound);
            }

            const std::string p_responseString = httpResponseMsg.getRawMessage();

            std::cout << std::endl;
            std::cout << lgname << "Handle message: request = " << httpMsg.getRequest() << std::endl;
            std::cout << lgname << "--------------: response = " << p_responseString << std::endl << std::endl;

            write(_clientSocket, p_responseString.c_str(), strlen(p_responseString.c_str()) - 1);

        }
        if (!p_handler.hasRawData()) {
            shutdown(_clientSocket, SHUT_RDWR);
            close(_clientSocket);
            break;
        }
    }

    *m_sharedMem = 0;

    return true;
}

bool Worker::isError()
{
    return false;
}
