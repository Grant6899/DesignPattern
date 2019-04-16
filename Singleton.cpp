/*************************************************************************
	> File Name: Singleton.cpp
	> Author: Grant Liu
	> Mail: ymliu6899@gmail.com
	> Created Time: Tue Apr  9 09:42:23 2019
 ************************************************************************/

#include<iostream>
using namespace std;

// Keypoints:
// Ensure that a class has just a single instance
// Provide a global access point to that instance

// Examples:
// Unique database connection, global config

class Singleton{
private:
    Singleton();
    static Singleton* _instance;

public:
    // not thread-safe
    Singleton* Singleton::getInstance(){
        if(!_instance)
            _instance = new Singleton();
        return _instance;
    }
};

Singleton* Singleton::_instance = 0;


// thread-safe with lock: safe, not effcient
class Singleton{
private:
    Singleton();
    static Singleton* _instance;
    mutex _mutex;

public:
    //thread-safe
    Singleton* Singleton::getInstance(){
        lock_guard<mutex> lock(_mutex); // not necessary to lock after instance created and all threads are reading it
        if(!_instance)
            _instance = new Singleton();
        return _instance;
    }
};



// thread-safe with double check lock: cannot be used
class Singleton{
private:
    Singleton();
    static Singleton* _instance;
    mutex _mutex;

public:
    //thread-safe
    Singleton* Singleton::getInstance(){
        if(!_instance){
            lock_guard<mutex> lock(_mutex); // only add lock when no instance created yet
            if(!_instance) // cannot remove this line. for two threads running after first check, they will both create a new instance
                _instance = new Singleton();
                /*
                    reorder at CPU level:
                        Expected order:
                            (1) allocate memory
                            (2) contruct object at the memory
                            (3) return the address to the memory and assign it to _instance

                        sometimes CPU may execute (1)(3)(2) at runtime. 

                    Consider below scnario:
                        thread 1 running at step(3) while object is not created yet
                        thread 2 observes there _instance is not null and returns it for use
                */

        }
        return _instance;
    }
};


// thread-safe with double check lock after c++11
class Singleton{
private:
    Singleton();
    static std::atomic<Singleton*> _instance;
    mutex _mutex;

public:
    //thread-safe
    Singleton* Singleton::getInstance(){
        Singleton* tmp = _instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire); // acquire memory fence
        if(!tmp){
            lock_guard<mutex> lock(_mutex); // only add lock when no instance created yet
            tmp = m_instance.load(std::memory_order_relaxed);
            if(!tmp){ // cannot remove this line. for two threads running after first check, they will both create a new instance
                tmp = new Singleton();
                std::atomic_thread_fence(std::memory_order_release); // release memory fence
                _instance.store(tmp, memory_order_relaxed);
            }
        }
        return tmp;
    }
};
