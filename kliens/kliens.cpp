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
    delete kliensServ;
    kliensServ = new Server(1, port);
    //send name to server
    sender(encode.getString(felhasznalonev));
    cout<<"sent name to server"<<endl;
}

void kliens::sendname()
{
    string send;
    string recive;
    while (true)
    {
        cout<<"felhasznalonev: ";
        getline(cin, felhasznalonev);
        send = encode.getString(felhasznalonev);
        //send
        sender(send);
        //recive
        recive = rec();
        //error msg
        if (recive[0] == 's')
        {
            cout << recive.substr(1) << endl;
        }
        //connect to nameserver
        else
        {
            port = decode.decInt(recive);
            connectToServ();
            return;
        }
    }
    throw out_of_range("not supposed to be here");
    return;
}

std::string kliens::rec()
{
    string rec;
    try
    {
        //nameServer kuldi a valaszt
        rec = kliensServ->Recive(kliensServ->SockToServ);
    }
    catch (disconected &e)
    {
        cout << "disconnected" << endl;
        exit(-1);
    }
    return rec;
}

void kliens::sender(std::string send)
{
    try
    {
        kliensServ->Sending(send);
    }
    catch (disconected &e)
    {
        cout << "disconnected" << endl;
        exit(-1);
    }
}







