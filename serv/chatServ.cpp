#include "./chatServ.h"

using namespace std;

chatServer::chatServer(int port)
{
    commChat = new Server(port);
    commNameS = new Server(1,54001);
    cout<<"here1.5"<<endl;
}

chatServer::~chatServer()
{
    cout<<"server destructor"<<endl;
    delete commChat;
    delete commNameS;
}



