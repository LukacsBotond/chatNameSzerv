#include "klisend.h"
#include "../common/Server.h"  
#include "../common/EnValues.h" 
#include <iostream>
#include <sstream>

using namespace std;

EnValues enkode;

int getPortFromNameS(Server &kliensToNamereg){
    cout<<"Varas a portra"<<endl;
    string ret = enkode.getString("?");
    kliensToNamereg.Sending(ret);
    ret = kliensToNamereg.Recive(kliensToNamereg.SockToServ).substr(1);
    int port = stoi(ret);
    return port;
}

void sendname(Server &kliens){
    
    while (true){

        string name;
        cout << "Irjon egy felhasznalo nevet: ";
        getline(cin, name);
        string ret = enkode.getString(name);
        kliens.Sending(ret);
        //kliens.Recive(kliens.)

    }
}

bool decodeSend(string userInput){
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    if(userInput == "-all"){

    }

}