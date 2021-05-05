#include "./support.h"
#include "./klisend.h"

using namespace std;

void cleanup(void){
    cout<<"cleanup"<<endl;
    delete kliens;
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   // cleanup and close up stuff here  
   // terminate program  
   exit(signum);  
}
