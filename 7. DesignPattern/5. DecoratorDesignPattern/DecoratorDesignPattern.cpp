// it is going to be like recursion
//           ______________
//           |            |
//           |An Decorator|
//           |            |
//           |            |
//           |            |
//           ______________
//                 \
//                  \
//                   \
//                 ___^__________
//                 |            |
//                 |An Decorator|
//                 |            |
//                 |            |
//                 |            |
//                 ______________
//                        \
//                         \ 
//                        __^___________
//                        |            |
//                        |An Decorator|
//                        |            |
//                        |            |
//                        |            |
//                        ______________
//                              \
//                               \
//                                \
//                              ___^__________
//                              |            |
//                              |MainFunction|
//                              |            |
//                              |            |
//                              |            |
//                              ______________
#include <iostream>
#include <string>
using namespace std;

class ICharactor{
    public:
    virtual string getAbility() const = 0;
    virtual ~ICharactor(){} 
};

class Mario : public ICharactor{
    public:
    string getAbility() const override {
        return "Mario";
    }
};

class DecoratorCharactor : public ICharactor{
    protected:
    ICharactor* ICharMario;
    public:
    DecoratorCharactor(ICharactor* c){
        this->ICharMario = c;
    }
};

class HeightUp : public DecoratorCharactor{
    public:
    HeightUp(ICharactor* c) : DecoratorCharactor(c) { } 
    string getAbility() const override{
        return ICharMario->getAbility() + "Height uped" ;
    }
};

class GunPowerUp : public DecoratorCharactor{
    public:
    GunPowerUp(ICharactor* c) : DecoratorCharactor(c) { } 
    string getAbility() const override{
        return ICharMario->getAbility() + "GUn power  uped" ;
    }
};

class StarPowerUp : public DecoratorCharactor{
    public:
    StarPowerUp(ICharactor* c) : DecoratorCharactor(c) { } 
    string getAbility() const override{
        return ICharMario->getAbility() + "Star power uped" ;
    }
};

int main(){
    ICharactor* mario = new Mario();
    cout << "Basic Charactor: " << mario->getAbility() << endl;

    mario = new HeightUp(mario);
    cout << "HightUp Charactor: " << mario->getAbility() << endl;
    mario = new GunPowerUp(mario);
    cout << "GunPowerUp Charactor: " << mario->getAbility() << endl;
    mario = new StarPowerUp(mario);
    cout << "StarPowerUp Charactor: " << mario->getAbility() << endl;

    delete mario;
    return 0;
}