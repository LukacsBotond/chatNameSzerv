#include "./chatServ.h"
#include "./supportServ.h"
#include <csignal>
#include <chrono>
#include <thread>

using namespace std;

//thread for chat
struct thread_data
{
};

void *accept(void *threadarg)
{
    cout << "accept loop starts" << endl;
    while (true)
    {
        chatServ->commChat->accepter();
        int ksock = chatServ->commChat->connetedToMe.back();
        chatServ->commChat->unblock(ksock);
        cout << "klient connected to chatServer" << endl;
    }
}

void *rec(void *threadarg)
{
    string rec;
    while (true)
    {
        cout << "szerver rec:" << endl;
        for (auto const &ksock : chatServ->commChat->connetedToMe)
        {
            chatServ->commChat->unblock(ksock);
            cout << "rec:" << ksock << endl;
            try
            {
                rec = chatServ->commChat->Recive(ksock);
            }
            catch (disconected &e)
            {
                cout << "disconnected" << endl;
                chatServ->commChat->connetedToMe.remove(ksock);
                close(ksock);
                continue;
            }
            catch (noData &e)
            {
                continue;
            }
            cout << "uzenet: " << rec.substr(1) << endl;
        }
        //miutan vegignezte az egeszet megall egy keveset
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main(int argc, char **argv)
{
    cout << "server starts" << endl;
    int number = getPort(argv);
    atexit(cleanup);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    chatServ = new chatServer(number);
    pthread_t threads[2];
    struct thread_data td[2];
    int rc = pthread_create(&threads[0], NULL, accept, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    rc = pthread_create(&threads[0], NULL, rec, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    while (true)
    {
        int tot = chatServ->getConnectedKlient();
        string sen = chatServ->encoder.getString(to_string(tot));
        chatServ->commNameS->Sending(sen);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    //thread for communicating with nameserver

    return 0;
}