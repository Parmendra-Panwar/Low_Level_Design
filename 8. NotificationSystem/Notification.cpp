#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*============================ Decorators ===========================*/
class INotification{
    public:
    virtual string getContent() const = 0;

    virtual ~INotification() {}
};

class SimpleNotification: public INotification{
    private:
    string text;
    public:
    SimpleNotification(const string& text){
        this->text = text;
    }
    string getContent() const override {
        return text;
    }
};

class INotification_decorator: public INotification{
    private:
    INotification* notification;
    public:
    INotification_decorator(INotification* n){
        notification = n;
    }
    virtual ~INotification_decorator() {
        delete notification;
    }
};

class TimeStemp_Decorator: public INotification_decorator{
    private:
    INotification* notification;
    public:
    // injection (getting and setting) of INotification 
    TimeStemp_Decorator(INotification* n): INotification_decorator(n) {}

    string getContent() const override {
        return notification->getContent() + "13/12/2025";
    }
};

class Signature_Decorator: public INotification_decorator{
    private:
    INotification* notification;
    string signature;
    public:
    Signature_Decorator(INotification* n, const string& str): INotification_decorator(n) {
        signature = str;
    }

    string getContent() const override {
        return notification->getContent() + signature;
    }
};

/*============================ Observer ===========================*/

class IObserver{
    public:
    virtual void update() = 0;
    virtual ~IObserver(){}
};

class IObservable{
    public:
    virtual void add(IObserver * obs) = 0;
    virtual void removeObs(IObserver * obs) = 0;
    virtual void notify() = 0;
    
    virtual ~IObservable(){}
};

class NotificationObservable: public IObservable{
    private:
        vector<IObserver *> observers;
        INotification* cNotification;
    public:
        void add(IObserver * obs) override {
            observers.push_back(obs);
        };
        void removeObs(IObserver *obs) override{
            observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
        }
    // virtual void notify() = 0;
};






int main(){

    return 0;
}