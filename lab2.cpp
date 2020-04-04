#include "lab2.h"
#include <cstring>
#include <semaphore.h>
#include <map>

#define MAIN lab2_init
#define Q 4
#define in_range(n) = 0; i < n; i++
#define NUMBER_OF_THREADS 11

std::map<char, pthread_t*> tid;
std::map<char, sem_t*> sem;

pthread_mutex_t lock;

// sem_t semF, semE, semG, semH;

using func = void* (*)(void*);

unsigned int lab2_thread_graph_id() 
{
    return 4;
}

const char* lab2_unsynchronized_threads()
{
    return "bcde";
}

const char* lab2_sequential_threads()
{
    return "efgh";
}

void *thread_a(void *ptr);
void *thread_b(void *ptr);
void *thread_c(void *ptr);
void *thread_d(void *ptr);
void *thread_e(void *ptr);
void *thread_f(void *ptr);
void *thread_g(void *ptr);
void *thread_h(void *ptr);
void *thread_i(void *ptr);
void *thread_k(void *ptr);
void *thread_m(void *ptr);
func fabric(char chose);

void doSmth(std::string name);
void wait(std::string flow);
void createThread(std::string flow);
void init();
void init_sems(const std::string &flow);
void destroy_sems(const std::string &flow);
void destroy_sems(const std::map<char, sem_t*> &flow);

int MAIN()
{
    init();
    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    try
    {
        init_sems(*(new std::string(lab2_sequential_threads())));
    }
    catch(char &item)
    {
        std::cerr << "Semaphore " << item <<" init failed" << std::endl;
        return 1;
    }
    createThread("acde");
    while(pthread_join(*tid['m'], NULL) != 0);
    std::cout << std::endl;
    pthread_mutex_destroy(&lock);
    destroy_sems(sem);

    return 0;
}

void init_sems(const std::string &flow)
{
    for(auto it : flow)
    {
        sem.insert(std::pair<char, sem_t*>(it, new sem_t));
        if(sem_init(sem[it], 0 , 1))
            throw it;       
    }
}
void destroy_sems(const std::string &flow)
{
    for(auto it :flow)
        sem_destroy(sem[it]);
}

void destroy_sems(const std::map<char, sem_t*> &flow)
{
    for(auto it : flow)
        sem_destroy(it.second);
}

void init()
{
    std::string flow ("abcdefghikm");
    for(auto it : flow)
        tid.insert(std::pair<char, pthread_t*>(it, new pthread_t()));
}
void doSmth(std::string name)
{
    for (int i in_range(Q))
    {
        pthread_mutex_lock(&lock);
        std::cout << name << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
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

func fabric(char chose)
{
    switch(chose)
    {
        case 'a':
            return thread_a;
        case 'b':
            return thread_b;
        case 'c':
            return thread_c;
        case 'd':
            return thread_d;
        case 'e':
            return thread_e;
        case 'f':
            return thread_f;
        case 'k':
            return thread_k;
        case 'h':
            return thread_h;
        case 'i':
            return thread_i;
        case 'g':
            return thread_g;
        case 'm':
            return thread_m;
        default:
            return NULL;
        }
}

void *thread_a(void *ptr)
{
    doSmth("a");
    createThread("b");
    return ptr;
}

void *thread_b(void *ptr)
{
    // std::cout << "whrer am i" << std::endl;

    doSmth("b");
    wait("c");
    createThread("gh");
    return ptr;
}
void *thread_c(void *ptr)
{
    doSmth("c");
    return ptr;
}
void *thread_d(void *ptr)
{
    doSmth("d");
    doSmth("d");
    doSmth("d");
    createThread("f");
    return ptr;
}
void *thread_e(void *ptr)
{
    doSmth("e");
    doSmth("e");
    sem_wait(sem['e']);
    doSmth("e");
    doSmth("e");
    sem_post(sem['f']);
    wait("fg");
    createThread("ik");
    return ptr;
}
void *thread_f(void *ptr)
{
    sem_wait(sem['f']);
    doSmth("f");
    sem_post(sem['g']);
    return ptr;
}
void *thread_g(void *ptr)
{
    sem_wait(sem['g']);
    doSmth("g");
    doSmth("g");
    sem_post(sem['h']);
    return ptr;
}
void *thread_h(void *ptr)
{
    sem_wait(sem['h']);
    doSmth("h");
    doSmth("h");
    doSmth("h");
    wait("ik");
    createThread("m");
    return ptr;
}
void *thread_i(void *ptr)
{
    doSmth("i");
    return ptr;
}
void *thread_m(void *ptr)
{
    doSmth("m");
    return ptr;
}

void *thread_k(void *ptr)
{
    doSmth("k");
    return ptr;
}