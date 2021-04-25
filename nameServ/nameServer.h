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

using namespace std;
class nonblock
{
};

class nameServer
{
private:
    NameSem* semafor;
    DeValues decoder;
    EnValues encoder;
    
public:
    nameServer();
    ~nameServer();
    void unblock(int ksock);
    //kert-e a socket
    bool recive(int ksock);
    bool send(int ksock);
    void acceptKliens();
    void acceptServ();
    Server* NameregToKliens;
    Server* checkServers;
    priority_queue<Server> aktivServer;
};

#endif