#include "./NameSem.h"
#include <iostream>

using namespace std;



NameSem::NameSem(/* args */)
{
    if ((semid = semget(IPC_PRIVATE, 1, 0660 | IPC_CREAT)) < 0)
    {
        cout << "semget error" << endl;
        exit(-1);
    }
    short init[1] = {1};
    if (semctl(semid, 0, SETALL, init) < 0)
    {
        cout << "INIT\n";
        exit(-1);
    }
}

NameSem::~NameSem()
{
    cout<<"sem destructor"<<endl;
    semctl(semid, 0, IPC_RMID, 0);
}

void NameSem::semup()
{
    if (semop(semid, &up, 1) < 0)
    {
        cout << "Sem up error" << endl;
        throw SemErr();
    }
}

void NameSem::semdown()
{
    if (semop(semid, &down, 1) < 0)
    {
        cout << "Sem down error" << endl;
        throw SemErr();
    }
}