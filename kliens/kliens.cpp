#include "kliens.h"

using namespace std;

kliens::kliens(/* args */)
{ //at start connect to nameServer
    kliensServ = new Server(1, 54000);
}

kliens::~kliens()
{
    delete kliensServ;
}

void kliens::connectToServ()
{
    kliensServReal = new Server(1, port);
    //send name to server
    sender(encode.getString(this->felhasznalonev),true);
    cout << "sent name to server " << this->felhasznalonev << endl;
}

void kliens::sendname()
{
    string send;
    string recive;
    while (true)
    {
        cout << "felhasznalonev: ";
        getline(cin, this->felhasznalonev);
        cout << "felhasznalonev: " << this->felhasznalonev << endl;
        send = encode.getString(this->felhasznalonev);
        //send
        sender(send,false);
        //recive
        recive = rec(false);
        //error msg
        if (recive[0] == 's')
        {
            cout << recive.substr(1) << endl;
        }
        //connect to nameserver
        else
        {
            port = decode.decInt(recive);
            cout<<port<<endl;
            connectToServ();
            return;
        }
    }
    throw out_of_range("not supposed to be here");
    return;
}

std::string kliens::rec(bool server)
{
    string rec;
    try
    {
        //nameServer kuldi a valaszt
        if (server)
        {
            rec = kliensServReal->Recive(kliensServReal->SockToServ);
        }
        else
        {
            rec = kliensServ->Recive(kliensServ->SockToServ);
        }
    }
    catch (disconected &e)
    {
        cout << "disconnected" << endl;
        exit(-1);
    }
    return rec;
}

void kliens::sender(std::string send, bool server)
{
    try
    {
        if (server)
        {
            kliensServReal->Sending(send);
        }
        else
        {
            kliensServ->Sending(send);
        }
    }
    catch (disconected &e)
    {
        cout << "disconnected" << endl;
        exit(-1);
    }
}
