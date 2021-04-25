#include "../common/Server.h"
#include "../common/EnValues.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

DeValues decoder;
EnValues encoder;
priority_queue<Server> aktivServer;

struct thread_data
{
    Server *NameregToKliens;
};
//kliensnek kuldi a legkevesbe terhelt szerver portjat
void *recv(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    string rec;
    while (true)
    {
        for (auto const &ksock : my_data->NameregToKliens->connetedToMe)
        {
            if (fcntl(ksock, F_GETFL) & O_NONBLOCK)
            {
                cout << "socket is non-blocking" << endl;
                // Put the socket in non-blocking mode:
                if (fcntl(ksock, F_SETFL, fcntl(ksock, F_GETFL) | O_NONBLOCK) < 0)
                {
                    cout << "nem sikerult non-blockingba tenni" << endl;
                }
            }
            try
            {
                rec = my_data->NameregToKliens->Recive(ksock);
            }
            catch (out_of_range &e)
            {
                cout << "cliens disconnected" << endl;
                my_data->NameregToKliens->connetedToMe.remove(ksock);
            }
            if (rec.size() == 0)
            {
                continue;
            }
            //nincs server inditva, kell egyet inditani
            if(aktivServer.top().connetedToMe.size() == 0){

            }
            int used = aktivServer.top().connetedToMe.size();
            cout << used << endl;

            string ret = encoder.getString(to_string(used));
        }
    }
}

int main()
{

    pthread_t threads[1];
    struct thread_data td[1];
    Server *nameRegKliens = new Server(54000);
    td[0].NameregToKliens = nameRegKliens;
    int rc = pthread_create(&threads[0], NULL, recv, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    //ha van tulterhelt szerver akkor indit meg egyet
    //idonkent vegigmegy a szervereken, hogy megkerdezze
    //hogy mennyire van leterhelve

    return 0;
}