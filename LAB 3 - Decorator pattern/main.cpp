#include <iostream>
using namespace std;

//We have a class Vector which has two coordinates - (x,y), also it has
// simple string return  fuction for eachcoordinate and simple print operation "<x> , <y>".
// I want to use Decorator pattern to add  more complex print function like this: "[<x>, <y>]"

class VectorComponent {
public:
    virtual ~VectorComponent(){}
    virtual string getstringX(){}
    virtual string getstringY(){}
    virtual void print(){}
};

class Vector : public VectorComponent{
public:
    Vector(int a, int b){
        x=a;
        y=b;
    }
    string getstringX() override {
        return to_string(x);
    }
    string getstringY() override {
        return to_string(y);
    }
    void print() override{
        cout<<this->getstringX() << " , " << this->getstringY();
    }
private:
    int x;
    int y;
};

class Decorator : public VectorComponent{
protected:
    VectorComponent* VecComp;
public:
     // just delegates all known tasks to Vector
    Decorator(VectorComponent* Vec):VecComp(Vec){
    }
    string getstringX() override{
        return this->VecComp->getstringX();
    }
    string getstringY()  override{
        return this->VecComp->getstringY();
    }

};
class BracketDecorator: public Decorator{
public:
    BracketDecorator(VectorComponent* VecComp): Decorator(VecComp){
    }
    void print()override{
        cout<<"["+Decorator::getstringX()+", "+Decorator::getstringY()+"]";
    }
};

void printVector(VectorComponent* Vec){
    Vec->print();
}

int main() {
    VectorComponent* simpleVector = new Vector(2,5);
    // so we have simple print from Vector:
    cout<<"Original Vector print(): ";
    printVector(simpleVector);
    cout<<endl;
    VectorComponent* BracDec1 = new BracketDecorator(simpleVector);
    cout<<"Decorated Vector print(): ";
    printVector(BracDec1);
    cout<<endl;
    return 0;
}
