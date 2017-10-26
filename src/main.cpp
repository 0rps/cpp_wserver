#include <iostream>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "listener.h"

#include <list>

// /home/box/final/final -h <ip> -p <port> -d <directory>

const int constWorkersCount = 8;

static const char *optString = "h:p:d:";

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

void runServer(int *_sharedMemory, const std::list<int> &_childPids, const std::list<int> &_childSockets, const std::string &_ip, const int _port) {
    std::string message = "My pid is " + std::to_string(getpid());
    std::cout << message << std::endl;

    for (auto it = _childPids.begin(); it != _childPids.end(); it++) {
        if ( *it != -1) {
            int status;
            waitpid(*it, &status, 0);
            std::cout << "Server: child process with pid = " << *it << " finished with status = " << status << std::endl;
        }
    }

    for (int i = 0; i < _childPids.size(); i++) {
        std::cout << "Server: from " << i << " shared cell read " <<_sharedMemory[i] << " value" << std::endl;
    }
}

void runClient(int* _sharedMemoryElement, const int _number, const std::string &_dir, const int _sockerFd) {
    std::string message = "My pid is " + std::to_string(getpid());
    std::cout << message << std::endl;

    *_sharedMemoryElement = getpid();
}

void runManagerAndWorkers(struct Parameters &_params, const int _clientsCount) {
    int* sharedMemory = (int*)allocateSharedMemory(_clientsCount, sizeof(int));
    for (int i = 0; i < constWorkersCount; i++) {
        sharedMemory[i] = -1;
    }

    pid_t pid;
    int currentNumber = 0;

    std::list<int> p_childsPids;
    std::list<int> p_childSockets;
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

    std::cout << "Params: '" << params.ip << "', port:'" << params.port << "', dir:'" << params.dir << "'" << std::endl << std::endl;

    runManagerAndWorkers(params, constWorkersCount);

    std::cout << "Exit pid = " << getpid() << std::endl;
    return 0;
}
