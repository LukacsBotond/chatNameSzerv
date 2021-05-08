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
//client connects and send the name, it shouldn't be a duplicate
//name as the nameServ already checked it
void *accept(void *threadarg)
{
    int port = chatServ->commChat->port;
    cout << "SZERVER: " << chatServ->commChat->port << " "
         << "accept loop starts" << endl;
    while (true)
    {
        string rec;
        chatServ->commChat->accepter();
        int ksock = chatServ->commChat->connetedToMe.back();
        try
        {
            rec = chatServ->commChat->Recive(ksock);
            cout<<"SZERVER: "<<" uj felhasznalo: "<< rec.substr(1)<<endl;
            chatServ->felhasznalok.insert({rec.substr(1), port});
        }
        catch (disconected &e)
        {
            cout << "SZERVER: " << chatServ->commChat->port << " "
                 << "disconnected" << endl;
            chatServ->commChat->connetedToMe.remove(ksock);
            close(ksock);
            continue;
        }
        chatServ->commChat->unblock(ksock);
        cout << "SZERVER: " << chatServ->commChat->port << " "
             << "klient connected to chatServer" << endl;
    }
}

//rec from client
void *rec(void *threadarg)
{
    string rec;
    while (true)
    {
        //cout <<"SZERVER: "<< chatServ->commChat->port <<" "<< "szerver rec:" << endl;
        vector<int> torol;
        for (auto const &ksock : chatServ->commChat->connetedToMe)
        {
            try
            {
                //cout << "SZERVER: " << chatServ->commChat->port << " "
                //     << "szerver rec:" << endl;
                rec = chatServ->commChat->Recive(ksock);
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
            cout << "SZERVER: " << chatServ->commChat->port << " " << rec.substr(1) << endl;
        }

        for (unsigned int i = 0; i < torol.size(); i++)
        {
            cout << "SZERVER: "
                 << "disconnected" << endl;
            close(torol.at(i));
            chatServ->commChat->connetedToMe.remove(torol.at(i));
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
        cout << "SZERVER: " << chatServ->commChat->port << " Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    rc = pthread_create(&threads[0], NULL, rec, (void *)&td[0]);
    if (rc)
    {
        cout << "SZERVER: " << chatServ->commChat->port << " "
             << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    while (true)
    {
        int tot = chatServ->getConnectedKlient();
        //send int when sending connected users
        string sen = chatServ->encoder.getString(tot);
        chatServ->commNameS->Sending(sen);
        //cout <<"SZERVER: "<< chatServ->commChat->port <<" sender" <<sen<<" |" <<tot<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    //thread for communicating with nameserver

    return 0;
}