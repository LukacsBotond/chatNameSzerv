#include "./chatServ.h"
#include <sstream>

using namespace std;

chatServer::chatServer(int port)
{
    commChat = new Server(port);
    commNameS = new Server(1, 54001);
}

chatServer::~chatServer()
{
    cout <<"SZERVER: "<< chatServ->commChat->port <<" " << "server destructor" << endl;
    string filename = "./";
    filename += to_string(commChat->port);
    int result = remove(filename.c_str());
    if (result == 0)
    {
        cout <<"SZERVER: "<< chatServ->commChat->port <<" " << "File is deleted\n"
             << endl;
    }
    else
    {
        cout <<"SZERVER: "<< chatServ->commChat->port <<" " << "Unable to delete.\n"
             << endl;
    }
    delete commChat;
    delete commNameS;
}

int chatServer::getConnectedKlient()
{
    return this->commChat->connetedToMe.size();
}

void chatServer::decodMsg(std::string msg){
    string buf;
    stringstream ss(msg);
    //elso szo kivevese
    ss >> buf;
    /*
    if (buf == "-priv" || buf == "-p")
    {
        return SendPriv(msg.substr(buf.size()+1));
    }
    */

}


