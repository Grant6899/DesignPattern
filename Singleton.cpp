/*************************************************************************
	> File Name: Singleton.cpp
	> Author: Grant Liu
	> Mail: ymliu6899@gmail.com
	> Created Time: Tue Apr  9 09:42:23 2019
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class Singleton{
private:
    Singleton();
    static Singleton* _instance;

public:
    static Singleton* getInstance(){
        if(!_instance)
            _instance = new Singleton();
        return _instance;
    }
};

Singleton* Singleton::_instance = 0;
