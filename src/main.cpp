#include <iostream>
#include <string>

#include <unistd.h>
#include <stdlib.h>

#include "listener.h"

// /home/box/final/final -h <ip> -p <port> -d <directory>

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


int main(int argc, char** argv) {

    std::cout << "Start server!" << std::endl;

    struct Parameters params;
    if (false == parseParameters(&params, argc, argv)) {
        std::cerr << "Parameters parsing error" << std::endl;
        return 0;
        exit(EXIT_FAILURE);
    }

    std::cout << "Params: '" << params.ip << "', port:'" << params.port << "', dir:'" << params.dir << "'" << std::endl << std::endl;

    Listener p_listener(params.ip, params.port, params.dir);
    p_listener.start();

    std::cout << "Exit server!" << std::endl;
    return 0;
}
