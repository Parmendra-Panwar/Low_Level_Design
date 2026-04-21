#include <iostream>
using namespace std;

// LLP (Low Level Layer) called Implementation
class Engine{
    public:
    virtual void start() = 0;
    virtual string name() = 0;
};

class PetrolEngine : public Engine{
    public:
    void start() override {
        cout<<"PetrolEngine Started"<<endl;
    };
    string name() override{
        return "Petrol";
    }
};

class ElectricEngine : public Engine{
    public:
    void start() override {
        cout<<"Electric Started"<<endl;
    };
    string name() override{
        return "Electric";
    }
};

// HLP (High level layer) called Abstraction
class Car{
    public:
    Engine* e;
    Car(){}
    virtual void drive() = 0;
    ~Car(){
        delete e;
    }
};

class SUVCar : public Car{
    public:
    Engine* e;
    SUVCar(Engine* e){
        this->e = e;
    }
    void drive() override{
        e->start();
        cout << "Driving SUV How's engine is " << e->name() << endl; 
    }
};

class SedanCar : public Car{
    public:
    Engine* e;
    SedanCar(Engine* e){
        this->e = e;
    }
    void drive() override{
        e->start();
        cout << "Driving Sedan How's engine is " << e->name() << endl; 
    }
};


int main(){
    Engine* e1 = new PetrolEngine();
    Engine* e2 = new ElectricEngine();
    Car* car1 = new SUVCar(e1);
    Car* car2 = new SedanCar(e1);
    car1->drive();
    car2->drive();

    delete car2;
    delete car1;
    delete e1;
    delete e2;
    return 0;
}