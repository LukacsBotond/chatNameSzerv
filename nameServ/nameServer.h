#ifndef nameServer_H
#define nameServer_H

#include "../common/Server.h"
#include "../common/EnValues.h"
#include "../common/NameSem.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <set>
#include <map>

using namespace std;

struct USED{
    int port;
    int aktiveUser;
    int sock;

    bool operator<(const USED &other) const
    {
        return this->aktiveUser < other.aktiveUser;
    }

    bool operator==(const USED &other) const
    {
        if(this->aktiveUser == other.aktiveUser && other.sock == this->sock && other.port == this->port)
        {
            return true;
        }
        return false;
    }

};

class nameServer
{
private:
    NameSem* semafor;
public:
    std::map<std::string,int> felhasznalok;
    DeValues decoder;
    EnValues encoder; 
    Server* NameregToKliens;
    Server* checkServers;
    std::set<USED> aktivServer;
    std::set<USED> aktivServerold;
    set<int> usedPort; 

    nameServer();
    ~nameServer();
    void unblock(int ksock);
    //kert-e a socket
    string recive(int ksock);
    void sendPort(int ksock,std::string felhasznalo);
    void acceptKliens();
    void acceptServ();

    void startNewServer();

    USED findBySocket(int sock);

    void getPortForUser(std::string cimzett, USED Ssock);
    //true ha szabad a nev
    //false ha nem
    bool checkName(std::string name);

    ///////printerek

    void printAktivServer();
};

inline nameServer* nameServ;

#endif