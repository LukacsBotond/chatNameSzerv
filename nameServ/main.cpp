#include "./nameServer.h"
#include "./NameSem.h"
#include "./support.h"
#include <csignal>

using namespace std;

struct thread_data
{
    nameServer *nameServ;
};

//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    this_thread::sleep_for(chrono::milliseconds(500000));
    string rec;
    while (true)
    {
        my_data->nameServ->acceptKliens();
        cout << "som" << endl;
        for (auto const &ksock : my_data->nameServ->NameregToKliens->connetedToMe)
        {
            my_data->nameServ->unblock(ksock);
            try
            {
                rec = my_data->nameServ->recive(ksock);
            }
            catch (disconected &e)
            {
            }
            catch (noData &e)
            {
                continue;
            }
            try{
                my_data->nameServ->send(ksock);
            }
            catch(disconected &e){ 
            }
        }
        //miutan vegignezte az egeszet megall egy keveset
        this_thread::sleep_for(chrono::milliseconds(500));
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
    td[0].nameServ = nameServ;
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
            USED tmp = Ssock;
            try
            {
                rec = nameServ->recive(Ssock.sock);
            }
            catch (disconected &e)
            {
                nameServ->aktivServer.erase(tmp);
                nameServ->usedPort.erase(tmp.port);
            }
            catch (noData &e){
                continue;
            }
            
            int used = nameServ->decoder.decInt(rec);
            cout<<used<<endl;
            tmp.aktiveUser = used;
        }
        nameServ->printAktivServer();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}