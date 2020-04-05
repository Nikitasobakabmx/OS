#include "lab2.h"
#include <map>
#include <string> 
#include <cstring>

#include "defines.h"

class myThread{
public:
    char name;
    std::map<char, myThread*> *tid = nullptr;
    pthread_t *thread = nullptr;
    pthread_mutex_t *lock = nullptr;
    using func = void* (*)(void*);

    myThread(char name = 0,
        std::map<char, myThread*> *tid = nullptr, 
        pthread_mutex_t *lock = nullptr)
    {
        this->tid = tid;
        this->name = name;
        if(lock != nullptr)
            this->lock = lock;
        else
            this->lock = new pthread_mutex_t;

        // this->thread; //= pthread_create(tid[it], nullptr, fabric(it), nullptr);
        // if(thread  != 0)
        //     std::cerr << "Can't create thread. Error: " << strerror(thread) << std::endl;
    }

    func run(int times = 1, 
        std::string create = "", 
        std::string waiting = "", 
        sem_t *semA = nullptr, 
        sem_t *semB = nullptr, 
        int repiat_with = 0, 
        int repiat_until = 0)
    {
        func result = [=, *this, *semA, *semB](void *ptr)
        {            
            for(int i = 0; i < times; i++)
                if(i > repiat_with && repiat_until > i)
                    doSmth(this->name, semA, semB);
                else
                    doSmth(this->name);
            wait(waiting, this->tid);
            createThread(create);
            return ptr;
        };
        return result;
        
    }
    static std::map<char, myThread*>* fabric(std::string sequence, pthread_mutex_t *lock = nullptr)
    { 
        std::map<char, myThread*> *tmp = new std::map<char, myThread*>();
        for(auto it : sequence)
            tmp->insert(std::pair<char, myThread*>(it, (new myThread(it, tmp, lock))));
        return tmp;
    }

    void doSmth(std::string name, sem_t *semA = nullptr, sem_t *semB = nullptr)
    {
        if(semA != nullptr)
        {
            std::cout << "sem" << std::endl;
            sem_wait(semA); // catch mutex
        }
        for (int i in_range(Q))
        {
            pthread_mutex_lock(lock);
            std::cout << name << std::flush;
            pthread_mutex_unlock(lock);
            computation();   
        }
        if(semB != nullptr)    
            sem_post(semB); // release mutex
    }
    static void wait(std::string flow, std::map<char, myThread*> *tid)
    {
        for(auto it : flow)
        {
            while(pthread_join(*(*tid)[it]->thread, nullptr) != 0);
        }
    }

    void createThread(std::string flow)
    {
        for(auto it : flow)
        {
            auto err = pthread_create((*tid)[it]->thread, nullptr, (*tid)[it]->run(), nullptr);
            if(err  != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        }        
    }
};