#ifndef nameServer_H
#define nameServer_H

#include "../common/Server.h"
#include "../common/EnValues.h"
#include "./NameSem.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <set>

using namespace std;
class nonblock
{
};

struct USED{
    int port;
    int aktiveUser;
    int sock;

    bool operator<(const USED &other) const
    {
        return this->aktiveUser < other.aktiveUser;
    }
};

class nameServer
{
private:
    NameSem* semafor;
public:
    DeValues decoder;
    EnValues encoder;    
    nameServer();
    ~nameServer();
    void unblock(int ksock);
    //kert-e a socket
    string recive(int ksock);
    void send(int ksock);
    void acceptKliens();
    void acceptServ();

    void startNewServer();

    USED findBySocket(int sock);
    ///////printerek

    void printAktivServer();

    Server* NameregToKliens;
    Server* checkServers;
    std::set<USED> aktivServer;
    set<int> usedPort;
};

inline nameServer* nameServ;

#endif