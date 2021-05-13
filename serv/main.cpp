#include "./chatServ.h"
#include "./supportServ.h"
#include <fstream>
#include <csignal>
#include <chrono>
#include <thread>

using namespace std;

//thread for chat
struct thread_data
{
};

void *piperead(void *threadarg){
    string port = to_string(chatServ->commChat->port);
    pipMy.open("./"+port,ios::in | ios::out);
    if(pipMy.fail())
    {
        cout << "pipe hiba" << endl;
        exit(-100);
    }
    
    string line;
    while (true)
    {
        getline(pipMy, line);
        cout<<"SZERVER: pipe get: "<<line<<endl;
        chatServ->decodMsg(line);
    }
}

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
            USER tmp;
            tmp.port = port;
            tmp.sock = ksock;
            chatServ->felhasznalok.insert({rec.substr(1), tmp});
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
            chatServ->decodMsg(rec.substr(1));
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
    pthread_t threads[3];
    struct thread_data td[3];
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

    rc = pthread_create(&threads[0], NULL, piperead, (void *)&td[0]);
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
        chatServ->sendToNameS(sen);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    //thread for communicating with nameserver

    return 0;
}