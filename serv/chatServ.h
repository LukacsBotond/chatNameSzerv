
#ifndef chatServ_H
#define chatServ_H
#include "../common/Server.h"
#include "../common/DeValues.h"
#include "../common/EnValues.h"
#include <iostream>
#include <map>

class chatServer
{
private:
    void SendPriv(std::string);
public:
    std::map<std::string,int> felhasznalok;
    DeValues decoder;
    EnValues encoder;
    Server* commChat;
    Server* commNameS;
    chatServer(int port);
    ~chatServer();
    int getConnectedKlient();

    void decodMsg(std::string);

};

inline chatServer* chatServ;

#endif