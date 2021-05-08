#ifndef kliens_H
#define kliens_H

#include <iostream>
#include "../common/Server.h"
#include "../common/DeValues.h"
#include "../common/EnValues.h"

class kliens
{
private:
    void connectToServ();
public:
    int port = -1;
    DeValues decode;
    EnValues encode;
    std::string felhasznalonev;
    Server *kliensServ;
    Server *kliensServReal;
    kliens();
    ~kliens();

    int getPortFromNameS(Server &kliensToNamereg);

    //ask new names till it is not in use
    //then recive the port to connect to the server
    void sendname();
    std::string rec(bool server);
    void sender(std::string send,bool server);
};

inline kliens *KLIENS;

#endif