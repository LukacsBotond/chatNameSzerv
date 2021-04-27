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
    delete[] NameregToKliens;
    delete[] checkServers;
    delete[] semafor;
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
    int port;
    while (true)
    {
        semafor->semdown();
        //ha nincs aktiv szerver akkor var, mig lesz
        if (aktivServer.size() == 0 || aktivServer.top().aktiveUser >= 5)
        {
            semafor->semup();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        else
        {
            port = aktivServer.top().port;
            semafor->semup();
        }
    }
    cout << port << " "<< aktivServer.top().aktiveUser << endl;
    string ret = encoder.getString(to_string(port));

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

void nameServer::startNewServer()
{
    cout << "start new server" << endl;
    int random;
    string sys = "./szerver ";

    std::mt19937 rng(56236);
    std::uniform_int_distribution<int> gen(54100, 54200); // uniform, unbiased
    random = gen(rng);

    while(true){
        //talalt egy ures portot
        if(usedPort.find(random) == usedPort.end()){
            sys += to_string(random);
            usedPort.insert(random);
            break;
        }
        if(random >= 54200){
            random = 54100;
        }
        else{
            random++;
        }
    }
    system(sys.c_str());
}
