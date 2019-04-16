/*************************************************************************
	> File Name: Vistor.cpp
	> Author: Grant Liu
	> Mail: ymliu6899@gmail.com
	> Created Time: Mon Apr 15 19:21:31 2019
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class ElementA;
class ElementB;

class Visitor{
public:
    // pre design for future additional functionality
    virtual void visitElementA(ElementA& element) = 0;
    virtual void visitElementB(ElementB& element) = 0;
    virtual ~Visitor(){}
};

// new functionality
class Visitor1 : public Visitor{
public:
    void visitElementA(ElementA& element) override{
        cout << "Visitor1 visiting ElementA\n";
    }

    void visitElementB(ElementB& element) override{
        cout << "Visitor1 visiting ElementB\n";
    }
};

class Visitor2 : public Visitor{
public:
    void visitElementA(ElementA& element) override{
        cout << "Visitor2 visiting ElementA\n";
    }

    void visitElementB(ElementB& element) override{
        cout << "Visitor2 visiting ElementB\n";
    }
};

class Element{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Element(){}
};

class ElementA: public Element{
public:
    void accept(Visitor& visitor) override{
        visitor.visitElementA(*this);
    }
};

class ElementB: public Element{
public:
    void accept(Visitor& visitor) override{
        visitor.visitElementB(*this);
    }
};

int main(){
    Visitor1 v2;
    ElementB eb;
    eb.accept(v2);
    return 0;
}
