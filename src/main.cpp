#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "string.h"

#include "listener.h"
//#include "httphandler.h"
#include "worker.h"
#include "server.h"

// /home/box/final/final -h <ip> -p <port> -d <directory>

const int constWorkersCount = 4;

static const char *optString = "h:p:d:";
//static std::string staticDir;

struct Parameters {

    Parameters() : port(-1) {}

    std::string dir;
    int port;
    std::string ip;

    bool isValid() const {
        return dir.length() > 0 && port > 0 && ip.length() > 0;
    }
};

bool parseParameters(struct Parameters *_params, int argc, char** argv) {
using namespace std;

//    cout << "read argv" << endl;
//    for (int i = 0; i < argc; i++) {
//        cout << "param " << i << " = " << argv[i] << endl;
//    }

//    cout << endl << endl;
//    char opt;
//    while( (opt = getopt(argc, argv, optString)) != -1) {
//        cout << "opt = " << opt << ", param = " << optarg << endl;

//    }

//    cout << endl << endl;
    char opt;
    while ((opt = getopt(argc, argv, optString)) != -1) {
        std::string p((const char*)optarg);
        switch (opt) {
        case 'p':
            _params->port = std::stoi(p);
            break;
        case 'h':
            _params->ip = p;
            break;
        case 'd':
            _params->dir = p;
            break;
        default:
            break;
        }
    }

    return _params->isValid();
}

void* allocateSharedMemory(const int _memoryElementsCount, const int _elementSize) {

    int fd = shm_open("/server_shm_000001", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        std::cerr << "Couldn't exec shm_open " << std::endl;
        return NULL;
    }

    const int p_size = _memoryElementsCount * _elementSize;

    if (ftruncate(fd, _memoryElementsCount * _elementSize) == -1) {
        std::cerr << "Couldn't exec ftruncate" << std::endl;
        return NULL;
    }

    void* addr = mmap(NULL, p_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        return NULL;
    }

    return addr;
}

std::pair<int,int> createUnixSocketPair() {
    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, sv) == -1) {
        return std::pair<int,int>(-1, -1);
    } else {
        return std::pair<int,int>(sv[0], sv[1]);
    }
}

//void handleSocket(int _socketFd, const std::string _dir) {
//    if (_socketFd <= 0) {
//        return;
//    }

//    char buffer[72];
//    const int bufferSize = sizeof(buffer);

//    FileExtractor p_fileExtractor(_dir);
//    HttpHandler p_handler;

//    while(true) {
//        int count = read(_socketFd, buffer, bufferSize);
//        if (count <= 0) {
//            close(_socketFd);
//            break;
//        }

//        p_handler.addRawData(buffer, count);

//        while(p_handler.hasMessages()) {
//            HttpMessage httpMsg = p_handler.pop();
//            std::string relPath = httpMsg.getRequest();

//            HttpMessage httpResponseMsg(true);

//            if (p_fileExtractor.fileExists(relPath)) {
//                int contentErr;
//                std::string content = p_fileExtractor.getFileContent(relPath, contentErr);
//                if (contentErr >= 0 ) {
//                    httpResponseMsg.setCode(MT_OK);
//                    httpResponseMsg.setBody(content);
//                } else if (contentErr == -1) {
//                    httpResponseMsg.setCode(MT_NotFound);
//                } else if (contentErr == -2) {
//                    httpResponseMsg.setCode(MT_ServerError);
//                }
//            } else {
//                httpResponseMsg.setCode(MT_NotFound);
//            }

//            const std::string p_responseString = httpResponseMsg.getRawMessage();

//            std::cout << std::endl;
//            std::cout << "Handle message: request = " << httpMsg.getRequest() << std::endl;
//            std::cout << "--------------: response = " << p_responseString << std::endl << std::endl;

//            write(_socketFd, p_responseString.c_str(), strlen(p_responseString.c_str()) - 1);

//        }
//        if (!p_handler.hasRawData()) {
//            shutdown(_socketFd, SHUT_RDWR);
//            close(_socketFd);
//            break;
//        }
//    }
//}

void runServer(int *_sharedMemory, const std::vector<int> &_childPids, const std::vector<int> &_childSockets, const std::string &_ip, const int _port) {
    std::string message = "My pid is " + std::to_string(getpid());
    std::cout << message << std::endl;

    Listener listener(_ip, _port);

    if (false == listener.start()) {
        return;
    }

    Server p_server(_sharedMemory);
    for (size_t i = 0; i < _childPids.size(); i++) {
        p_server.addWorker(i, _childPids[i], _childSockets[i]);
    }

    int socketFd = listener.nextSocket();
    while (socketFd >= 0) {
//        Worker p_worker(0, socketFd, NULL, staticDir);
//        p_worker.tryToHandle();
        if (socketFd > 0)  {
            p_server.scheduleNewClient(socketFd);
        }
        socketFd = listener.nextSocket();
    }

    //char data[] = "GET / HTTP/1.1\r\nContent-Length: 1234\r\n\r\n";
    //int i = sizeof(data);

    //p_handler.addRawData(data, sizeof(data)-1);



//        if (res > 0) {
//            int count = read(res, buf, sizeof(buf));
//            p_handler.addRawData(buf, count);

//            if (p_handler.hasMessages()) {

//                std::cout << "handler has messages: " << p_message.getRequest() << std::endl;
//            } else {
//                std::cout << "No messages" << std::endl;
//            }
//        }
//    }

//    std::string p_childmessage = "YOYOYO! to = ";

//    int j = 0;
//    for (auto it = _childSockets.begin(); it != _childSockets.end(); it++) {
//        if ( *it != -1) {
//            //int status;
//            std::string temp = p_childmessage + std::to_string(j);
//            write(*it, temp.c_str(), temp.size() + 1);
//            std::cout << "Server: send =  " << temp << std::endl;
//        }
//        j++;
//    }

//    for (auto it = _childPids.begin(); it != _childPids.end(); it++) {
//        if ( *it != -1) {
//            int status;
//            waitpid(*it, &status, 0);
//            std::cout << "Server: child process with pid = " << *it << " finished with status = " << status << std::endl;
//        }
//    }

//    for (int i = 0; i < _childPids.size(); i++) {
//        std::cout << "Server: from " << i << " shared cell read " <<_sharedMemory[i] << " value" << std::endl;
//    }


}

void runClient(int* _sharedMemoryElement, const int _number, const std::string &_dir, const int _sockerFd) {
    std::string message = "My pid is " + std::to_string(getpid());
    std::cout << message << std::endl;

    Worker p_worker(_number, _sockerFd, _sharedMemoryElement, _dir);
    while(true) {
        int fd = p_worker.waitClientSocket();
        if (fd < 0) {
            break;
        }

        if (fd > 0) {
            p_worker.tryToHandle(fd);
        }
    }

//    char buf[512];
//    buf[0] = 0;
//    int count = 0;
//    while(true) {
//        sleep(1);
//        count = read(_sockerFd, buf, 512);
//        std::cout << "Readed " << count << " bytes" << std::endl;
//        if (count == -1) {
//            if (errno == EWOULDBLOCK) {
//                ///
//            } else {
//                break;
//            }
//        }


//    }
//    std::cout << "Client with pid = " << getpid() << " read: " << buf << std::endl;

//    *_sharedMemoryElement = getpid();
}

void runManagerAndWorkers(struct Parameters &_params, const int _clientsCount) {
    int* sharedMemory = (int*)allocateSharedMemory(_clientsCount, sizeof(int));
    for (int i = 0; i < constWorkersCount; i++) {
        sharedMemory[i] = -1;
    }

    pid_t pid;
    int currentNumber = 0;

    std::vector<int> p_childsPids;
    std::vector<int> p_childSockets;
    bool successFlag = false;

    while (currentNumber < _clientsCount) {
        std::pair<int,int> sockPair = createUnixSocketPair();
        if ((pid = fork()) == -1 || sockPair.first == -1) { // error
            std::cerr << "fork failed or socket creation failed: pid = " << pid << ", socket = " << sockPair.first << "," << sockPair.second <<  std::endl;
            if (sockPair.first != -1) {
                shutdown(sockPair.first, SHUT_RDWR);
                shutdown(sockPair.second, SHUT_RDWR);
                close(sockPair.first);
                close(sockPair.second);
            }
        } else if (pid == 0) { // child
            close(sockPair.first);
            for (auto it = p_childSockets.begin(); it != p_childSockets.end(); it++) {
                if (*it != -1) { close(*it); }
            }
            runClient(sharedMemory + currentNumber, currentNumber, _params.dir, sockPair.second);
            return;
        } else if (pid > 0) { // parent
            successFlag = true;
            close(sockPair.second);
        }

        p_childsPids.push_back(pid);
        p_childSockets.push_back(sockPair.first);

        currentNumber++;
    }

    if (!successFlag) {
        std::cerr << "No workers were forked! Server wasn't started!" << std::endl;
        return;
    }

    runServer(sharedMemory, p_childsPids, p_childSockets, _params.ip, _params.port);
}

int main(int argc, char** argv) {

    std::cout << "Starting pid=" << getpid() << std::endl;

    struct Parameters params;
    if (false == parseParameters(&params, argc, argv)) {
        std::cerr << "Parameters parsing error" << std::endl;
        return 0;
        exit(EXIT_FAILURE);
    }

//    staticDir = params.dir;

    std::cout << "Params: '" << params.ip << "', port:'" << params.port << "', dir:'" << params.dir << "'" << std::endl << std::endl;

    runManagerAndWorkers(params, constWorkersCount);

    std::cout << "Exit pid = " << getpid() << std::endl;
    return 0;
}
