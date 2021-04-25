#include "klisend.h"
#include "../common/Server.h"  
#include "../common/EnValues.h" 
#include <iostream>
#include <sstream>

using namespace std;

EnValues enkode;

int getPortFromNameS(Server &kliensToNamereg){
    string ret = enkode.getString("?");
    kliensToNamereg.Sending(ret);
    int port = stoi(kliensToNamereg.Recive(kliensToNamereg.SockToServ));
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