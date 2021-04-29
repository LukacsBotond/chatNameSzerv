#include "./nameServer.h"
#include <random>

using namespace std;

nameServer::nameServer(/* args */)
{
    NameregToKliens = new Server(54000);
    checkServers = new Server(54001);
    semafor = new NameSem;
}

nameServer::~nameServer()
{
    cout << "nameServ Destruktor" << endl;
    delete NameregToKliens;
    delete checkServers;
    delete semafor;
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

string nameServer::recive(int ksock)
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
        throw disconected();
    }
    return rec;
}

void nameServer::send(int ksock)
{
    int port;
    while (true)
    {
        semafor->semdown();
        //ha nincs aktiv szerver akkor var, mig lesz
        auto itr = aktivServer.begin();
        USED tmp = *itr;
        if (aktivServer.size() == 0 || tmp.aktiveUser >= 3)
        {
            semafor->semup();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        else
        {
            port = tmp.port;
            semafor->semup();
            break;
        }
    }
    string ret = encoder.getString(to_string(port));

    try
    {
        NameregToKliens->Sending(ret);
    }
    catch (disconected &e)
    {
        //nem sikerult elkuldeni
        NameregToKliens->connetedToMe.remove(ksock);
        close(ksock);
        throw disconected();
    }
}

void nameServer::acceptKliens()
{
    NameregToKliens->accepter();
}

void nameServer::acceptServ()
{
    checkServers->accepter();
    int newServ = checkServers->connetedToMe.back();
    unblock(newServ);
    USED tmp;

    tmp = findBySocket(-1);

    aktivServer.erase(tmp);
    tmp.sock = newServ;
    aktivServer.insert(tmp);
}

void nameServer::startNewServer()
{
    cout << "start new server" << endl;
    int random;
    string sys = "./szerver ";

    std::mt19937 rng(56236);
    std::uniform_int_distribution<int> gen(54100, 54200); // uniform, unbiased
    random = gen(rng);

    while (true)
    {
        //talalt egy ures portot
        if (usedPort.find(random) == usedPort.end())
        {
            sys += to_string(random) +" &";
            usedPort.insert(random);
            USED tmp;
            tmp.aktiveUser = 0;
            tmp.port = random;
            tmp.sock = -1;
            aktivServer.insert(tmp);
            system(sys.c_str());
            break;
        }
        if (random >= 54200)
        {
            random = 54100;
        }
        else
        {
            random++;
        }
    }
}

USED nameServer::findBySocket(int sock)
{
    for (auto it = aktivServer.begin(); it != aktivServer.end(); ++it)
    {
        USED tmp = *it;
        if (tmp.sock == sock)
        {
            return tmp;
        }
    }
    throw noData();
}

void nameServer::printAktivServer()
{
    int lenght = this->aktivServer.size();
    cout << "szerverek szama: " << lenght << endl;
    for (auto it = aktivServer.begin(); it != aktivServer.end(); ++it)
    {
        USED tmp = *it;
        cout << tmp.port << " " << tmp.aktiveUser << endl;
        //cout<<aktivServer.at(i).port<<" "<<aktivServer.at(i).aktiveUser<<endl;
    }
}
