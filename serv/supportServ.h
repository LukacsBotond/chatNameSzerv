#ifndef support_H
#define support_H

int getPort(char **argv);

void cleanup(void);

void signalHandler( int signum );

#endif