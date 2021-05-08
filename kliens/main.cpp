#include <iostream>
#include <string>
#include <vector>
#include "./kliens.h"
#include <csignal>
#include "./support.h"

using namespace std;

bool vege = false;

struct thread_data
{
};
//recive from server
void *recv(void *threadarg)
{
    while (true)
    {
        string rec;
        try
        {
            rec = KLIENS->kliensServ->Recive(KLIENS->kliensServ->SockToServ);
        }
        catch (disconected &e)
        {
            cout << "hiba a recive-ben";
            vege = true;
            pthread_exit(NULL);
        }
        rec = rec.substr(1);
        cout << "Recived: " << rec << endl;
    }
}

int main()
{
    cout << "klines start..." << endl;
    atexit(cleanup);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    pthread_t threads[1];
    struct thread_data td[1];
    KLIENS = new kliens();
    KLIENS->sendname();

    /*
    int rc = pthread_create(&threads[0], NULL, recv, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
*/
    string userInput;
    cout << "Lehetseges parancsok:\n";
    cout << "-all uzenet vagy -a uzenet :Mindenki aki csatlakozva van kuld egy uzenetet\n";
    cout << "-list vagy -l Visszateriti az aktiv felhasznalokat\n";
    cout << "-priv cimzett uzenet vagy -p cimzett uzenet :Privat uzenet kuldese egy felhasznalonak\n";
    do
    { //		Enter lines of text
        cout << "PARANCS>: ";
        getline(cin, userInput);
        userInput = KLIENS->encode.getString(userInput);
        try
        {
            KLIENS->kliensServReal->Sending(userInput);
        }
        catch (disconected &e)
        {
            cout << "disconnected" << endl;
            exit(-1);
        }
        /*
        if (!decodeSend(userInput))
        {
            cout << "Ismeretlen parancs, probalja ujra" << endl;
        }
        else
        {
            cout << "Sikeresen elkuldve\n";
        }
        */
    } while (!vege);

    return 0;
}
