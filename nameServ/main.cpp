#include "./nameServer.h"
#include "./NameSem.h"

using namespace std;

struct thread_data
{
    nameServer nameServ;
};

//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    while (true)
    {
        my_data->nameServ.acceptKliens();
        cout<<"som"<<endl;
        for (auto const &ksock : my_data->nameServ.NameregToKliens->connetedToMe)
        {
            my_data->nameServ.unblock(ksock);
            if (!my_data->nameServ.recive(ksock))
            {
                continue;
            }
            my_data->nameServ.send(ksock);
        }
        //miutan vegignezte az egeszet megall egy keveset
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    pthread_t threads[1];
    struct thread_data td[1];
    nameServer nameServ;
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

    while (true)
    {
        if (nameServ.aktivServer.size() == 0 || nameServ.aktivServer.top().connetedToMe.size() >= 4)
        {
            system("./szerver alma");
        }

        

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}