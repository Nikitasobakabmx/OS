#include <iostream>
#include <map>
#define in_range(n)  = 0; i < n; i++
std::map<char, pthread_t> tid;
 
void *thread_b(void *ptr)
{
    return ptr;
}

int main()
{
    for (int i in_range(10) )
        std::cout << i << std::endl;
    std::string init("abcd");
    for(auto it : init)
    {    
        pthread_t *tmp = new pthread_t();
        if(!pthread_create(tmp, NULL, thread_b, NULL))
        {    
            tid.insert(std::pair<char, pthread_t>(it, *tmp));
            pthread_join(tid[it], NULL);
            tid.erase(it);
        }
    }
    return 0;
}