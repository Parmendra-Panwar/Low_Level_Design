#include <iostream>
using namespace std;

class Employee {
    public:
    virtual ~Employee() {}
    virtual string getName() = 0;
};

class Leave{
    private:
    int d;
    Employee* u;

    public:
    Leave(int d, Employee* u){
        this->d = d;
        this->u = u;
    }
    int getLeaveDays(){
        return d;
    }
    string getLeaveUserName(){
        return u->getName();
    }
};

class EmployeeL1 : public Employee{
    public:
    string name;
    
    EmployeeL1(string name){
        this->name = name;
    }
    string getName() override{
        return name;
    }
};

class IApprover : public Employee {
    protected:
    IApprover* nextApprover = nullptr;
    public:
    virtual ~IApprover() {}
    void setNext(IApprover* e){
        nextApprover = e;
    }
    virtual void AprroveLeave(Leave* l){};
};

class EmployeeL2 : public IApprover{ // can approve up to 2 days leave
    public:
    string name;
    EmployeeL2(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }
    void AprroveLeave(Leave* l) override {
        if(l->getLeaveDays() <= 2){
            cout<<"[Level 2 have] " << name << "have Approved Leave <<"<<l->getLeaveUserName() <<"\n";
            return;
        }
        if(nextApprover == nullptr) {
            cout<<"Leave Can't be approved\n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class EmployeeL3 : public IApprover{ // can approve up to 5 days leave
    public:
    string name;
    EmployeeL3(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }
    void AprroveLeave(Leave* l) override {
        if(l->getLeaveDays() <= 5){
            cout<<"[Level 3 have] " << name << "have Approved Leave <<"<<l->getLeaveUserName() <<"\n";
            return;
        }
        if(nextApprover == nullptr) {
            cout<<"Leave Can't be approved\n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class EmployeeL4 : public IApprover{ // can approve up to 7 days leave
    public:
    string name;
    EmployeeL4(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }
    void AprroveLeave(Leave* l) override {
        if(l->getLeaveDays() <= 7){
            cout<<"[Level 4 have] " << name << "have Approved Leave <<"<<l->getLeaveUserName() <<"\n";
            return;
        }
        if(nextApprover == nullptr) {
            cout<<"Leave Can't be approved\n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class LeaveManagementSystem{
    private:
    static LeaveManagementSystem* instance;
    EmployeeL2* e2;
    EmployeeL3* e3;
    EmployeeL4* e4;
    
    LeaveManagementSystem(){
        e2 = new EmployeeL2("Amit");
        e3 = new EmployeeL3("Rhul");
        e4 = new EmployeeL4("priti");
        e2->setNext(e3);
        e3->setNext(e4);
    }

    public:
    static LeaveManagementSystem* getInstance(){
        if(instance == nullptr) instance = new LeaveManagementSystem();
        return instance;
    }
    Leave* createLeaveRequest(int days, Employee* e){
        return new Leave(days, e);
    }
    void SubmitForApproval(Leave* l){
        e2->AprroveLeave(l);
    }
    void deleteInstance(){
        delete e2;
        delete e3;
        delete e4;
    }
};
LeaveManagementSystem* LeaveManagementSystem::instance = nullptr;

int main(){
    LeaveManagementSystem* lms = LeaveManagementSystem::getInstance();

    Employee* e1 = new EmployeeL1("Karan");
    Leave* l = lms->createLeaveRequest(3, e1);
    lms->SubmitForApproval(l);

    lms->deleteInstance();
    delete e1;
    delete l;
    delete lms;
    return 0;
}