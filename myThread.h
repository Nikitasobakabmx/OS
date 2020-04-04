#include "lab2.h"
#include <map>
#include <string> 

class myThread{
private:
    std::string name;
    std::map<char, myThread*> *tid;
    int thread;
    using func = void* (*)(void*);
public:
    myThread(std::string &name = "", std::map<char, pthread_t*> &tid = nullptr)
    {
        this->tid = &tid;
        &(this->name) = &name;
        this->thread = pthread_create(tid[it], NULL, fabric(it), NULL);
        if(thread  != 0)
            std::cerr << "Can't create thread. Error: " << strerror(thread) << std::endl;
    }

    func run(int times = 1, srd::string create = "", std::string waiting = "", sem_t semA = nullptr, sem_t semB = nullptr, int repiat_with = 0, int repiat_until = 9999)
    {
        for(int i = 0; i < times; i++)
            if(i > repiat_with && repiat_until > i)
                doSmth(name, semA, semB);
            else
                doSmth(name);
        wait(waiting);
        createThread(create);
    }
    std::map<char, myThread*> fabric(std::string sequence)
    { 
        auto *tmp = new std::map();
        for(auto it : sequence)
            tmp->insert(std::pair<char, *myThread>(it, new myThread(it, tmp)));
        return tmp;
    }

    void doSmth(std::string name, sem_t *semA, sem_t *semB)
    {
        struct timespec ts;
        ts.tv_sec = 1;
        if(semA != NULL)
        {
            std::cout << "sem" << std::endl;
            sem_wait(semA); // catch mutex
        }
        for (int i in_range(Q))
        {
            
            pthread_mutex_lock(&lock);
            std::cout << name << std::flush;
            pthread_mutex_unlock(&lock);
            computation();
            
        }
        if(semB != NULL)    
            sem_post(semB); // release mutex
    }
    void wait(std::string flow)
    {
        for(auto it : flow)
        {
            while(pthread_join(*tid[it], NULL) != 0);
        }
    }

    void createThread(std::string flow)
    {
        for(auto it : flow)
        {
            auto err = pthread_create(tid[it], NULL, fabric(it), NULL);
            if(err  != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        }        
    }
    void createThread(std::string flow)
    {
        for(auto it : flow)
        {
            auto err = pthread_create(tid[it], NULL, fabric(it), NULL);
            if(err  != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        }        
    }
    }