#include "./chatServ.h"

using namespace std;

chatServer::chatServer(int port)
{
    cout<<"sadff"<<endl;
    commChat = new Server(port);
    cout<<"asd"<<endl;
    commNameS = new Server(1,54001);
}

chatServer::~chatServer()
{
    cout<<"server destructor"<<endl;
    delete[]commChat;
    delete[]commNameS;
}
