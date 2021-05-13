#include "./chatServ.h"
#include <sstream>
#include <fstream>

using namespace std;

chatServer::chatServer(int port)
{
    commChat = new Server(port);
    commNameS = new Server(1, 54001);
}

chatServer::~chatServer()
{
    cout << "SZERVER: " << chatServ->commChat->port << " "
         << "server destructor" << endl;
    string filename = "./";
    filename += to_string(commChat->port);
    int result = remove(filename.c_str());
    if (result == 0)
    {
        cout << "SZERVER: " << chatServ->commChat->port << " "
             << "File is deleted\n"
             << endl;
    }
    else
    {
        cout << "SZERVER: " << chatServ->commChat->port << " "
             << "Unable to delete.\n"
             << endl;
    }
    delete commChat;
    delete commNameS;
}

int chatServer::getConnectedKlient()
{
    return this->commChat->connetedToMe.size();
}

void chatServer::sendToNameS(string msg)
{
    try
    {
        commNameS->Sending(msg);
    }
    catch (disconected &e)
    {
        cout << "nameserver disconnected" << endl;
        exit(-1);
    }
}

string chatServer::recFromNameS()
{
    try
    {
        return commNameS->Recive(commNameS->SockToServ);
    }
    catch (disconected &e)
    {
        cout << "nameserver disconnected" << endl;
        exit(-1);
    }
}

void chatServer::decodMsg(std::string msg)
{
    string buf, buf1;
    stringstream ss(msg);
    //elso szo kivevese
    ss >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
    if (buf == "-priv" || buf == "-p")
    {
        ss >> buf1;
        return SendPriv(msg.substr(buf.size() + buf1.size() + 2), buf, buf1);
    }
}

////////////////////private

void chatServer::SendPriv(string msg, string comm, string cimzett)
{
    cout<<"Szerver Priv uzenet"<<endl;
    string rec;
    string sen1;
    auto user = felhasznalok.find(cimzett);
    //valaki mashoz van kapcsolodva a masik kliens
    if (user == felhasznalok.end())
    {
        cout<<"Szerver other server"<<endl;
        int port;
        //ask nameServer to which port the other is connected to
        sen1 = encoder.getString("-p" + cimzett);
        sendToNameS(sen1);
        rec = recFromNameS();
        port = decoder.decInt(rec);
        string sen = comm + " " + cimzett + " "+ msg;
        sendMsgPipe(sen, port);
    }
    else
    {
        string sen = "Priv msg: " + user->first + " |" + msg;
        sen = encoder.getString(sen);
        try
        {
            this->commChat->Sending(sen, user->second.sock);
        }
        catch (disconected &e)
        {
            cout << "SZERVER: "
                 << "disconnected" << endl;
            close(user->second.sock);
            chatServ->commChat->connetedToMe.remove(user->second.sock);
            felhasznalok.erase(user->first);
        }
    }
}

void chatServer::sendMsgPipe(string msg, int port)
{
    ofstream pip("./" + to_string(port));
    if (pip.fail())
    {
        cout << "pipe fail" << endl;
        pip.close();
        return;
    }
    pip << msg << endl;
    pip.close();
}
