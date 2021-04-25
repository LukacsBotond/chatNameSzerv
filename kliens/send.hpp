#ifndef send_H
#define send_H

#include "../common/Server.h"

int getPortFromNameS(Server &kliensToNamereg);

void sendname(Server &kliens);
bool decodeSend(string userInput);

#endif