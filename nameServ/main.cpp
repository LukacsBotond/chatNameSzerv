#include "./nameServer.h"
#include "../common/NameSem.h"
#include "./support.h"
#include <csignal>

using namespace std;

struct thread_data
{
};

void *acc(void *threadarg)
{
    cout<<"nameSzerv: " << "accept loop starts" << endl;
    while (true)
    {
        nameServ->NameregToKliens->accepter();
        int ksock = nameServ->NameregToKliens->connetedToMe.back();
        nameServ->NameregToKliens->unblock(ksock);
        cout  <<"nameSzerv: " << "klient connected to NameServ" << endl;
    }
}

//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    string rec;
    while (true)
    {
        vector<int> torol;
        for (auto const &ksock : nameServ->NameregToKliens->connetedToMe)
        {
            try
            {
                //string erkezik a nevvel
                rec = nameServ->recive(ksock);
                rec = rec.substr(1);
            }
            catch (disconected &e)
            {
                torol.push_back(ksock);
                continue;
            }
            catch (noData &e)
            {
                continue;
            }

            if(!nameServ->checkName(rec)){
                rec = nameServ->encoder.getString("foglalt a nev");
                nameServ->NameregToKliens->Sending(rec);
                continue;
            }
            try
            {
                nameServ->sendPort(ksock,rec);
            }
            catch (disconected &e)
            {
                torol.push_back(ksock);
            }
        }

        for(unsigned int i=0;i<torol.size();i++){
            cout <<"nameSzerv: " << "disconnected" << endl;
            close(torol.at(i));
            nameServ->NameregToKliens->connetedToMe.remove(torol.at(i));
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main()
{
    atexit(cleanup);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    pthread_t threads[2];
    struct thread_data td[2];
    nameServ = new nameServer;
    int rc = pthread_create(&threads[0], NULL, recv, (void *)&td[0]);
    if (rc)
    {
        cout <<"nameSzerv: " << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    rc = pthread_create(&threads[0], NULL, acc, (void *)&td[0]);
    if (rc)
    {
        cout <<"nameSzerv: " << "Error:unable to create thread," << rc << endl;
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
            cout <<"nameSzerv: " << "uj szerver elindult" << endl;
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