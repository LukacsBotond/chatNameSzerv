#include "./nameServer.h"
#include "../common/NameSem.h"
#include "./support.h"
#include <csignal>

using namespace std;

struct thread_data
{
};

//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    string rec;
    while (true)
    {
        nameServ->acceptKliens();
        int ksock = nameServ->NameregToKliens->connetedToMe.front();
        nameServ->NameregToKliens->unblock(ksock);
        try
        {
            rec = nameServ->recive(ksock);
        }
        catch (disconected &e)
        {
            cout << "disconnected" << endl;
        }
        catch (noData &e)
        {
            cout << "nem kuldott semmit" << endl;
            continue;
        }
        try
        {
            nameServ->sendPort(ksock);
        }
        catch (disconected &e)
        {
            cout << "disconnected" << endl;
        }
        close(ksock);
        nameServ->NameregToKliens->connetedToMe.pop_front();
    }
}

int main()
{
    atexit(cleanup);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    pthread_t threads[1];
    struct thread_data td[1];
    nameServ = new nameServer;
    int rc = pthread_create(&threads[0], NULL, recv, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    //ha van tulterhelt szerver akkor indit meg egyet
    //idonkent vegigmegy a szervereken, hogy megkerdezze
    //hogy mennyire van leterhelve
    srand(time(0));

    string rec;
    while (true)
    {
        auto itr = nameServ->aktivServer.begin();
        USED tmp = *itr;
        if (nameServ->aktivServer.size() == 0 || tmp.aktiveUser >= 5)
        {
            nameServ->startNewServer();
            this_thread::sleep_for(chrono::milliseconds(1000));
            nameServ->acceptServ();
            cout << "uj szerver elindult" << endl;
        }
        for (auto Ssock : nameServ->aktivServer)
        {
            nameServ->aktivServer.erase(Ssock);
            try
            {
                rec = nameServ->recive(Ssock.sock);
            }
            catch (disconected &e)
            {
                nameServ->aktivServer.erase(tmp);
                nameServ->usedPort.erase(tmp.port);
            }
            catch (noData &e)
            {
                continue;
            }
            int used = nameServ->decoder.decInt(rec);
            Ssock.aktiveUser = used;
            nameServ->aktivServer.insert(Ssock);
        }
        nameServ->printAktivServer();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}