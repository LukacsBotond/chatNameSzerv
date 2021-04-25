#include <iostream>
#include <vector>
#include "../common/Server.h"
#include "../common/EnValues.h"
#include "../common/DeValues.h"
#include "./klisend.h"

using namespace std;

DeValues decoder;
EnValues encoder;
bool vege = false;

struct thread_data
{
    int port;
    Server *kliens;
};
//recive from server
void *recv(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    while (true)
    {
        string rec;
        try{
        rec = my_data->kliens->Recive(my_data->kliens->SockToServ);
        }
        catch(disconected &e){
            cout<<"hiba a recive-ben";
            vege = true;
            pthread_exit(NULL);
        }
        int vecthossz = decoder.Decode255(rec.substr(0, 2));
        rec = rec.substr(3);
        cout << "Recived: " << rec << endl;
    }
}

int main()
{
    pthread_t threads[1];
    struct thread_data td[1];
    Server *kliensToNamereg = new Server(1, 54000);
    int port = getPortFromNameS(*kliensToNamereg);
    delete[] kliensToNamereg;

    Server *kliens = new Server(1, port);
    td[0].port = port;
    td[0].kliens = kliens;
    int rc = pthread_create(&threads[0], NULL, recv, (void *)&td[0]);
    if (rc)
    {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }

    string userInput;
    cout << "Lehetseges parancsok:\n";
    cout << "-all uzenet vagy -a uzenet :Mindenki aki csatlakozva van kuld egy uzenetet\n";
    cout << "-list vagy -l Visszateriti az aktiv felhasznalokat\n";
    cout << "-priv cimzett uzenet vagy -p cimzett uzenet :Privat uzenet kuldese egy felhasznalonak\n";
    do
    { //		Enter lines of text
        cout << "PARANCS>: ";
        getline(cin, userInput);
        if (!decodeSend(userInput))
        {
            cout << "Ismeretlen parancs, probalja ujra" << endl;
        }
        else
        {
            cout << "Sikeresen elkuldve\n";
        }
    } while (!vege);

    return 0;
}
