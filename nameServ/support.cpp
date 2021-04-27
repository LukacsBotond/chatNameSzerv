#include "./support.h"
#include "./nameServer.h"
using namespace std;

void cleanup(void){
    cout<<"cleanup"<<endl;
    delete[] nameServ;
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   // cleanup and close up stuff here  
   // terminate program  
   exit(signum);  
}
