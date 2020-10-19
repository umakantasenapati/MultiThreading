#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable  condVar;
bool flag=true;
void odd()
{
    for(auto i=1;i<20;i+=2)
    {
        unique_lock<mutex> ulock(mtx);
        condVar.wait(ulock,[](){return flag;});
        cout<<i<<endl;
        flag=false;
        condVar.notify_one();
    }
}
void even()
{
    for(auto i=2;i<20;i+=2)
    {
        unique_lock<mutex> ulockEven(mtx);
        condVar.wait(ulockEven,[](){return !flag;});
        cout<<i<<endl;
        flag=true;
        condVar.notify_one();
    }
}

int main()
{
    thread thdOdd(odd);
    thread thdEven(even);

    thdOdd.join();
    thdEven.join();

    return 0;
}
