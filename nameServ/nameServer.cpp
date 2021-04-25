#include "./nameServer.h"

using namespace std;

nameServer::nameServer(/* args */)
{
    NameregToKliens = new Server(54000);
    semafor = new NameSem;
}

nameServer::~nameServer()
{
    delete[]NameregToKliens;
    delete[]semafor;
}

void nameServer::unblock(int ksock)
{
    if (fcntl(ksock, F_GETFL) & O_NONBLOCK)
    {
        cout << "socket is non-blocking" << endl;
        // Put the socket in non-blocking mode:
        if (fcntl(ksock, F_SETFL, fcntl(ksock, F_GETFL) | O_NONBLOCK) < 0)
        {
            cout << "nem sikerult non-blockingba tenni" << endl;
            throw nonblock();
        }
    }
}

bool nameServer::recive(int ksock)
{
    string rec;
    try
    {
        rec = NameregToKliens->Recive(ksock);
    }
    catch (disconected &e)
    {
        cout << "cliens disconnected" << endl;
        NameregToKliens->connetedToMe.remove(ksock);
        close(ksock);
        return false;
    }
    if (rec.size() == 0)
    {
        return false;
    }
    return true;
}

bool nameServer::send(int ksock)
{
    int used;
    while (true)
    {
        semafor->semdown();
        //ha nincs aktiv szerver akkor var, mig lesz
        if (aktivServer.size() == 0 || aktivServer.top().connetedToMe.size() >= 5)
        {
            semafor->semup();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        else
        {
            used = aktivServer.top().connetedToMe.size();
            semafor->semup();
        }
    }
    cout << used << endl;
    string ret = encoder.getString(to_string(used));

    if (!NameregToKliens->Sending(ret))
    {
        //nem sikerult elkuldeni
        NameregToKliens->connetedToMe.remove(ksock);
        close(ksock);
        return false;
    }
    return true;
}

void nameServer::acceptKliens()
{
    NameregToKliens->accepter();
}

void nameServer::acceptServ()
{
    checkServers->accepter();
}
