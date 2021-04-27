
#ifndef chatServ_H
#define chatServ_H
#include "../common/Server.h"
#include <iostream>

class chatServer
{
private:
    Server* commChat;
    Server* commNameS;
public:
    chatServer(int port);
    ~chatServer();
};

inline chatServer* chatServ;

#endif