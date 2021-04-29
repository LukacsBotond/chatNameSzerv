#include "./chatServ.h"
#include "./supportServ.h"
#include <csignal>
#include <chrono>
#include <thread>

using namespace std;

//thread for chat


int main(int argc, char **argv)
{
    cout<<"server starts"<<endl;
    int number;
    atexit(cleanup);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    try
    {
        number = std::stoi(argv[1]);
        cout << number << endl;
    }
    catch (std::exception const &e)
    {
        cout << "nem szam erkezett" << endl;
        exit(-1);
    }
    if (number < 54100 || number > 54200)
    {
        cout << "hibas port erkezett" << endl;
        exit(-1);
    }
    cout<<"here1"<<endl;
    chatServ = new chatServer(number);
    //chatServ->commNameS->Sending(to_string(0));
    cout<<"here2"<<endl;
    while(true){
        string sen = chatServ->encoder.getString(to_string(0));
        chatServ->commNameS->Sending(sen);
        this_thread::sleep_for(chrono::milliseconds(10000));
    }
//thread for communicating with nameserver

    return 0;
}