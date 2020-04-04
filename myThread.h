#inclide "lab2.h"

class myThread{
private:
    std::string name;
public:
    myThread(std::string &name = "")
    {
        &(this->name) = &name;
    }

    void *run(void *ptr)
    {
        
    }
}