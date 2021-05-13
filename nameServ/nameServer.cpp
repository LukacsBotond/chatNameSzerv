#include "./nameServer.h"
#include <random>
#include <sys/stat.h>

using namespace std;

nameServer::nameServer(/* args */)
{
    NameregToKliens = new Server(54000);
    checkServers = new Server(54001);
    semafor = new NameSem;
}

nameServer::~nameServer()
{
    cout << "nameSzerv: "
         << "nameServ Destruktor" << endl;
    delete NameregToKliens;
    delete checkServers;
    delete semafor;
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
        throw disconected();
    }
    return rec;
}

void nameServer::sendPort(int ksock, string felhasznalo)
{
    int port;
    while (true)
    {
        semafor->semdown();
        //ha nincs aktiv szerver akkor var, mig lesz
        auto itr = this->aktivServer.begin();
        USED tmp = *itr;
        if (this->aktivServer.size() == 0 || tmp.aktiveUser >= 6)
        {
            semafor->semup();
            cout << "nameSzerv: "
                 << "Wait for new server" << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        else
        {
            port = tmp.port;
            semafor->semup();
            felhasznalok.insert({felhasznalo, port});
            break;
        }
    }
    string ret = encoder.getString(port);

    try
    {
        NameregToKliens->Sending(ret, ksock);
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
    //checkServers->unblock(newServ);
    USED tmp;

    tmp = findBySocket(-1);

    aktivServer.erase(tmp);
    tmp.sock = newServ;
    aktivServer.insert(tmp);
}

void nameServer::startNewServer()
{
    cout << "nameSzerv: "
         << "start new server" << endl;
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
            string pipename = "./";
            pipename += to_string(random);
            sys += to_string(random) + " &";
            usedPort.insert(random);
            USED tmp;
            tmp.aktiveUser = 0;
            tmp.port = random;
            tmp.sock = -1;
            aktivServer.insert(tmp);
            //make a named pipe for the server
            mkfifo(pipename.c_str(), 0666);
            //start the server
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

bool nameServer::checkName(string name)
{
    if (felhasznalok.find(name) == felhasznalok.end())
    {
        return true;
    }
    return false;
}

void nameServer::printAktivServer()
{
    if (aktivServer != aktivServerold)
    {
        int lenght = this->aktivServer.size();
        cout << "nameSzerv: "
             << "szerverek szama: " << lenght << endl;
        for (auto Ssock : nameServ->aktivServer)
        {
            cout << "nameSzerv: " << Ssock.port << " " << Ssock.aktiveUser << endl;
        }
    }
    aktivServerold = aktivServer;
}

//////////////////////////////////

void nameServer::getPortForUser(string cimzett, USED Ssock)
{
    string rec;
    auto user = felhasznalok.find(cimzett);
    //nincs ilyen felhasznalo
    if (user == felhasznalok.end())
    {
        rec = encoder.getString(-1);
    }
    else
    {
        rec = encoder.getString(user->second);
    }
    cout<<"nameSzerv: kikuldendo port: "<<rec<<" "<<rec.substr(3)<<endl;
    cout<<"sock: "<<Ssock.sock<<endl;
    try
    {
        this->checkServers->Sending(rec, Ssock.sock);
    }
    catch (disconected &e)
    {
        cout << "nameSzerv: "
             << "disconnected szerver" << endl;
        close(Ssock.sock);
        nameServ->aktivServer.erase(Ssock);
        nameServ->usedPort.erase(Ssock.port);
    }
}
