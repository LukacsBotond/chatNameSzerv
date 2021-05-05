#include "./supportServ.h"
#include "./chatServ.h"
using namespace std;

int getPort(char **argv){
    int number;
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
    return number;
}

void cleanup(void){
    cout<<"cleanup chatServ"<<endl;
    delete chatServ;
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   // cleanup and close up stuff here  
   // terminate program  
   exit(signum);  
}
