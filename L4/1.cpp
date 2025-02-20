#include <mutex>
#include <semaphore>
#include <atomic>
#include <barrier>
#include <condition_variable>

#include <thread>
#include <iostream>

using namespace std;

enum LockType{
    Mutex=1,
    Semaphore,
    SemaphoreSlim,
    Barrier,
    Spinlock,
    Spinwait,
    Monitor
};

class Locker{
    LockType lock_type;
    mutex mtx;
    counting_semaphore<1> sem;
    atomic_int sems;
    barrier<> bar;
    atomic_flag spinlock;
    atomic_bool spinwait;
    condition_variable con;
    bool is_monitor_locked;
    public:
    Locker(int mode,int thread_count):sem(1),bar(thread_count){
        lock_type=LockType(mode);
        sems.store(1);
        spinlock.clear();
        spinwait.store(false);
        is_monitor_locked=false;
    }
    void lock(){
        switch(lock_type){
            case LockType::Mutex:
                mtx.lock();
                break;
            case LockType::Semaphore:
                sem.acquire();
                break;
            case LockType::SemaphoreSlim:
                sems.wait(0);
                sems.store(0);
                break;
            case LockType::Barrier:
                break;
            case LockType::Spinlock:
                while (spinlock.test_and_set(memory_order_acquire)) {};
                break;
            case LockType::Spinwait:
                while (spinwait.exchange(true, std::memory_order_acquire)) {
                    this_thread::yield();
                    };
                break;
            case LockType::Monitor:
                {
                unique_lock<mutex> lock(mtx);
                con.wait(lock, [&]() { return !is_monitor_locked; });// Ожидаем, пока монитор не разблокируется
                is_monitor_locked = true;// Устанавливаем флаг блокировки монитора
                break;
                }
            default:
                cerr<<"Wrong lock type";
                throw;
        }
    }
    void unlock(){
        switch(lock_type){
            case LockType::Mutex:
                mtx.unlock();
                break;
            case LockType::Semaphore:
                sem.release();
                break;
            case LockType::SemaphoreSlim:
                sems.store(1);
                sems.notify_one();
                break;
            case LockType::Barrier:
                bar.arrive_and_wait();
                break;
            case LockType::Spinlock:
                spinlock.clear(memory_order_release);
                break;
            case LockType::Spinwait:
                spinwait.exchange(false, std::memory_order_release);
                break;
            case LockType::Monitor:
                {
                unique_lock<mutex> lock(mtx);
                is_monitor_locked = false; 
                con.notify_one();
                break;
                }
            default:
                cerr<<"Wrong lock type";
                throw;
        }
    }
};

int main(){
    unsigned thread_number,data_number,lock_number;
    cin>>thread_number;
    cin>>lock_number;
    cin>>data_number;
    Locker process_lock(lock_number,thread_number);
    auto process=[&](int thread_id){
        process_lock.lock();
        cout<<"Thread "<<thread_id<<" ";
        for(int i=0;i<data_number;i++)
            cout<<(char)(rand()%100+30);
        cout<<endl;
        process_lock.unlock();
    };
    thread *thread_pool=new thread[thread_number];
    for(int i=0;i<thread_number;i++)
        thread_pool[i]=thread(process,i);
    for(int i=0;i<thread_number;i++)
        thread_pool[i].join();
}
