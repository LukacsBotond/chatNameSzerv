#include "Server.h"
#include "../common/DeValues.h"

using namespace std;

//szerver mode
Server::Server(int port)
{
    // Create a socket
    this->listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cout << "Can't create a socket! Quitting" << endl;
        exit(1);
    }
    int opt = 1;
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        cout << "Failed to set SO_REUSEADDR option. " << strerror(errno) << "\n";
        exit(1);
    }
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        cout << "Failed to set SO_REUSEPORT option. " << strerror(errno) << "\n";
        exit(1);
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint = {0};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if ((bind(listening, (sockaddr *)&hint, sizeof(hint))) == -1)
    {
        cout << "bind failed\n";
        exit(-1);
    }
    listen(this->listening, SOMAXCONN);
}
//kliens mode
Server::Server(int kliens, int port){
    SockToServ = socket(AF_INET, SOCK_STREAM, 0);
    if (SockToServ == -1)
    {
        cout << "socket error" << endl;
        exit(1);
    }
    //	Create a hint structure for the server we're connecting with
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int res = connect(SockToServ, (sockaddr *)&hint, sizeof(hint));
    if (res == -1)
    {
        cout << "connect error" << endl;
        exit(1);
    }
    
}

Server::~Server()
{
    close(this->listening);
    close(this->SockToServ);
}

void Server::accepter(){
    cout<<"the server is wating for the klient"<<endl;
    // Tell Winsock the socket is for listening
    this->connetedToMe.push_back(accept(listening, (sockaddr *)&client, &clientSize));
}

string Server::Recive(int recFrom)
{
    int hossz = ReciveSize(recFrom);
    //cout<<hossz<<endl;
    vector<char> buf(hossz);
    int res = recv(recFrom, buf.data(), hossz, 0);
    int resch = resCheck(res);
    //nem kuldott uzenetet
    if(resch == -1){
        return "";
    }
    if (!resch)
    {
        cout << "EXIT RES\n";
        throw out_of_range("disconnected");
    }
    while (res < hossz)
    {
        vector<char> bufextra(hossz);
        int extra = recv(recFrom, bufextra.data(), hossz - res, 0);
        if (!resCheck(res))
        {
            cout << "EXIT RES\n";
            throw out_of_range("disconnected");
        }
        for (int i = 0; i < extra; i++)
            buf.at(i + res) = bufextra.at(i);
        res += extra;
    }
    string csomag(buf.begin(), buf.end());
    //cout << csomag << endl;
    return csomag;
}

bool Server::Sending(string message)
{
    int res = send(SockToServ, message.c_str(), message.size(), 0);
    if (!resCheck(res))
    {
        return false;
    }
    return true;
}

int Server::ReciveSize(int recFrom)
{
    vector<char> buf(2);
    int hossz;
    int res = recv(recFrom, buf.data(), 2, 0);
    if (!resCheck(res))
    {
        cout << "EXIT RES\n";
        throw out_of_range("disconnected");
    }
    while (res < 2)
    {
        vector<char> bufextra(2);
        int extra = recv(recFrom, bufextra.data(), 2 - res, 0);
        if (!resCheck(res))
        {
            cout << "EXIT RES\n";
            throw out_of_range("disconnected");
        }
        for (int i = 0; i < extra; i++)
            buf.at(i + res) = bufextra.at(i);
        res += extra;
    }
    string csomag(buf.begin(), buf.end());

    hossz = dekoder.Decode255(csomag);
    return hossz;
}

int Server::resCheck(int res)
{
    if (res < 0)
    {
        if(errno == EAGAIN || errno == EWOULDBLOCK){
            return -1;
        }
        cout << "RECV error\n";
        return 0;
    }
    if (res == 0)
    {
        cout << "kilepett\n";
        return 0;
    }
    return 1;
}
