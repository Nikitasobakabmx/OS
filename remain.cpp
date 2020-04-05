#include <iostream>
#include <map>
#include <semaphore.h>

#include "defines.h"
#include "myThread.h"
// #define in_range(n)  = 0; i < n; i++


int MAIN()
{
    std::map<char, myThread*> *tid = nullptr;  
    std::map<char, sem_t> *sems = nullptr;
    pthread_mutex_t *lock = new pthread_mutex_t;
    std::string seq("abscdefghim");
    tid = myThread::fabric(seq, lock);
    for(auto& it : *tid )
        it.second->run();
    myThread::wait(seq, (*tid)[seq[0]]->tid);
    return 0;
}