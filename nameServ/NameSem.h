#ifndef NameSem_H
#define NameSem_H

#include <sys/sem.h>
#include <sys/shm.h>

class SemErr
{
};

class NameSem
{
private:
    int semid;
    struct sembuf down = {0, -1, 0};
    struct sembuf up= {0, +1, 0};
public:
    NameSem(/* args */);
    ~NameSem();
    void semStart();
    void semup();
    void semdown();
};





#endif