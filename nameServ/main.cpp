#include "./nameServer.h"
#include "./NameSem.h"
#include "./support.h"
#include <csignal>

using namespace std;

struct thread_data
{
    nameServer* nameServ;
};

//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    this_thread::sleep_for(chrono::milliseconds(500000));
    while (true)
    {
        my_data->nameServ->acceptKliens();
        cout<<"som"<<endl;
        for (auto const &ksock : my_data->nameServ->NameregToKliens->connetedToMe)
        {
            my_data->nameServ->unblock(ksock);
            if (!my_data->nameServ->recive(ksock))
            {
                continue;
            }
            my_data->nameServ->send(ksock);
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

    while (true)
    {
        /*
        if (nameServ->aktivServer.size() == 0 || nameServ->aktivServer.top().aktiveUser >= 4)
        {
            nameServ->startNewServer();
            this_thread::sleep_for(chrono::milliseconds(10000));
        }
        */
        //wait till it starts up
        cout<<"varas a szerverre"<<endl;
        nameServ->acceptServ();
        cout<<"uj szerver elindult"<<endl;

        //this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}