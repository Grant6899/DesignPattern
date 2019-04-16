/*************************************************************************
	> File Name: Decorator.cpp
	> Author: Grant Liu
	> Mail: ymliu6899@gmail.com
	> Created Time: Mon Apr 15 21:14:35 2019
 ************************************************************************/

#include<iostream>

using namespace std;

class Notifier{
public:
    virtual void send(string msg) = 0;
    virtual ~Notifier(){};
};

class CallNotifier : public Notifier{
public:
    CallNotifier() = default;
    
    void send(string msg){
        cout << "Call sending: " << msg << endl;
    }

    virtual ~CallNotifier(){

    }
};

class BaseDecorator : public Notifier{
protected:
    Notifier* wrappee;
public:
    BaseDecorator(Notifier* notifier): wrappee(notifier){
    
    }

    virtual void send(string msg){
        wrappee->send(msg);
    }
};

class SMSDecorator : public BaseDecorator{
public:
    SMSDecorator(Notifier* notifier) : BaseDecorator(notifier){

    }

    void send(string msg){
        BaseDecorator::send(msg);
        cout << "SMS sending: " << msg << endl;
    }
};

class FaceBookDecorator : public BaseDecorator{
public:
    FaceBookDecorator(Notifier* notifier) : BaseDecorator(notifier){

    }

    void send(string msg){
        BaseDecorator::send(msg);
        cout << "FaceBook sending: " << msg << endl;
    }
};

class EmailDecorator : public BaseDecorator{
public:
    EmailDecorator(Notifier* notifier) : BaseDecorator(notifier){

    }

    void send(string msg){
        BaseDecorator::send(msg);
        cout << "Email sending: " << msg << endl;
    }
};

int main(){
    
    Notifier* s1 = new CallNotifier();
    Notifier* s2 = new FaceBookDecorator(s1);
    Notifier* s3 = new SMSDecorator(s2);

    s3->send("hello world");
    delete s1;
    delete s2;
    delete s3;
    return 0;
}
