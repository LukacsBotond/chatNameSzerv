
#ifndef chatServ_H
#define chatServ_H
#include "../common/Server.h"
#include "../common/DeValues.h"
#include "../common/EnValues.h"
#include <iostream>
#include <fstream>
#include <map>

struct USER{
    int port;
    int sock;
};

class chatServer
{
private:
    void SendPriv(std::string msg,std::string comm, std::string cimzett);

    void sendMsgPipe(std::string msg, int port);
public:
    std::map<std::string,USER> felhasznalok;
    DeValues decoder;
    EnValues encoder;
    Server* commChat;
    Server* commNameS;
    chatServer(int port);
    ~chatServer();
    int getConnectedKlient();

    void sendToNameS(std::string msg);
    std::string recFromNameS();

    void decodMsg(std::string);

};

inline chatServer* chatServ;
inline std::ifstream pipMy;

#endif