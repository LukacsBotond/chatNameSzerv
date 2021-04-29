#include "./supportServ.h"
#include "./chatServ.h"
using namespace std;

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
