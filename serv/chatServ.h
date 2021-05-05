
#ifndef chatServ_H
#define chatServ_H
#include "../common/Server.h"
#include "../common/DeValues.h"
#include "../common/EnValues.h"
#include <iostream>

class chatServer
{
public:
    DeValues decoder;
    EnValues encoder;
    Server* commChat;
    Server* commNameS;
    chatServer(int port);
    ~chatServer();
    int getConnectedKlient();
};

inline chatServer* chatServ;

#endif