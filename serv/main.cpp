#include "./chatServ.h"
#include "./supportServ.h"
#include <csignal>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{
    int number;
    atexit(cleanup);
    signal(SIGINT, signalHandler); 
    signal(SIGTERM, signalHandler); 
    try
    {
        number = std::stoi(argv[1]);
        cout<<number<<endl;
    }
    catch (std::exception const &e)
    {
       cout<<"nem szam erkezett"<<endl;
       exit(-1);
    }
    if(number < 54100 || number > 54200){
        cout<<"hibas port erkezett"<<endl;
        exit(-1);
    }
    cout<<number<<endl;
    chatServ = new chatServer(number);

    
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(5000));
    }
    
    return 0;
}