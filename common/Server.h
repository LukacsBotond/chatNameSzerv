#ifndef Szerver_H
#define Szerver_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../common/DeValues.h"

class disconected{
};

class Server
{
public:
    Server(){}
    Server(int port);
    Server(int kliens, int port);
    ~Server();
    std::string Recive(int recFrom);
    bool Sending(std::string message);
    void accepter();
    
    std::vector<int> getAllConnected();

    //ahova en vagyok csatlakozva
    int getToConnected();

    int SockToServ;
    //mindenki aki ram van csatlakozva, csak szerver
    std::list<int> connetedToMe;
    
    int port;
    int listening;
    int ReciveSize(int recFrom);
    int resCheck(int res);
    DeValues dekoder;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
};

#endif