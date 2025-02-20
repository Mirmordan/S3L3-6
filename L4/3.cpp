#include <vector>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <iostream>
using namespace std;
int main()
{
    unsigned people(5);
    cout<<people<<endl;
    vector <thread> thread_pool;
    vector <mutex> forks(people);
    vector <unsigned> data(people,0);
    auto deadlock=[&](unsigned id){
        while(true){
            forks[id].lock();
            forks[(id+1)%people].lock();
            data[id]++;
            forks[id].unlock();
            forks[(id+1)%people].unlock();
        }
    };
    counting_semaphore officiant(people-1);
    bool running=true;
    auto solution=[&](unsigned id){
        while(running){
            officiant.acquire();
            forks[id].lock();
            forks[(id+1)%people].lock();
            data[id]++;
            forks[id].unlock();
            forks[(id+1)%people].unlock();
            officiant.release();
        }
    };
    cout<<"solution"<<endl;
    for(int i=0;i<people;i++){
        thread_pool.emplace_back(solution,i);
        thread_pool[i].detach();
    }
    sleep(1);
    for(auto i:data)
        cout<<i<<" ";
    cout<<endl;
    sleep(1);
    running=false;
    for(auto i:data)
        cout<<i<<" ";
    cout<<endl;
    data=vector<unsigned>(people,0);
    thread_pool.clear();
    cout<<"deadlock"<<endl;
    for(int i=0;i<people;i++){
        thread_pool.emplace_back(deadlock,i);
        thread_pool[i].detach();
    }
    sleep(1);
    for(auto i:data)
        cout<<i<<" ";
    cout<<endl;
    sleep(1);
    for(auto i:data)
        cout<<i<<" ";
    cout<<endl;
}