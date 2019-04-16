/*************************************************************************
	> File Name: Proxy.cpp
	> Author: Grant Liu
	> Mail: ymliu6899@gmail.com
	> Created Time: Tue Apr 16 10:28:36 2019
 ************************************************************************/

#include<iostream>
using namespace std;

class Subject{
	virtual void request() = 0;
};

class RealSubject : public Subject{
public:
	void request(){
		cout << "request in real subject\n";
	}
};

class Proxy : public Subject{

public:
	Proxy();
	virtual ~Proxy();

	void request();

private:
	void afterRequest();
	void preRequest();	
	RealSubject *m_pRealSubject;

};

Proxy::Proxy(){
	//有人觉得 RealSubject对象的创建应该是在main中实现；我认为RealSubject应该
	//对用户是透明的，用户所面对的接口都是通过代理的；这样才是真正的代理； 
	m_pRealSubject = new RealSubject();
}

Proxy::~Proxy(){
	delete m_pRealSubject;
}

void Proxy::afterRequest(){
	cout << "Proxy::afterRequest" << endl;
}


void Proxy::preRequest(){
	cout << "Proxy::preRequest" << endl;
}


void Proxy::request(){
	preRequest();
	m_pRealSubject->request();
	afterRequest();
}

int main(){
	Proxy proxy;
	proxy.request();
	
	return 0;
}