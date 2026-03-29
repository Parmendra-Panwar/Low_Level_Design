#include <iostream>
using namespace std;


class Withdrawal{
    private:
    int Amount;
    public:
    Withdrawal(int Amount){
        this->Amount = Amount;
    }
    int getAmount(){
        return Amount;
    }
    void setAmount(int Amount){
        this->Amount = Amount;
    }
};

class noteAmount {
    protected:
    noteAmount* nextApprover = nullptr;
    public:
    virtual ~noteAmount() {}
    void setNext(noteAmount* e){
        nextApprover = e;
    }
    virtual void AprroveLeave(Withdrawal* w){};
};

class Thousand : public noteAmount{
    public:
    int numOfNote;
    Thousand(int numOfNote){
        this->numOfNote = numOfNote;
    }
    void AprroveLeave(Withdrawal* l) override {
        int askedAmt = l->getAmount();
        int provNotes= askedAmt/1000;
        int reminders= askedAmt%1000;
        int givable = min(numOfNote, provNotes);

        if(reminders == 0){
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 1000 Rupee Notes\n";
                numOfNote -= provNotes;
                return;
            }else if(givable > 0){
                cout<<givable <<" X 1000 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount(askedAmt - givable*1000);
            }
        }else{
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 1000 Rupee Notes\n";
                numOfNote -= provNotes;
                l->setAmount(reminders);
            }else if(givable > 0){
                cout<<givable <<" X 1000 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount((askedAmt - givable*1000));
            }
        }

        if(nextApprover == nullptr){
            cout<<"can't make payment Amount: "<<l->getAmount()<<" \n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class FiveHund : public noteAmount{
    public:
    int numOfNote;
    FiveHund(int numOfNote){
        this->numOfNote = numOfNote;
    }
    void AprroveLeave(Withdrawal* l) override {
        int askedAmt = l->getAmount();
        int provNotes= askedAmt/500;
        int reminders= askedAmt%500;
        int givable = min(numOfNote, provNotes);

        if(reminders == 0){
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 500 Rupee Notes\n";
                numOfNote -= provNotes;
                return;
            }else if(givable > 0){
                cout<<givable <<" X 500 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount(askedAmt - givable*500);
            }
        }else{
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 500 Rupee Notes\n";
                numOfNote -= provNotes;
                l->setAmount(reminders);
            }else if(givable > 0){
                cout<<givable <<" X 500 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount((askedAmt - givable*500));
            }
        }

        if(nextApprover == nullptr){
            cout<<"can't make payment Amount: "<<l->getAmount()<<" \n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class OneHund : public noteAmount{
    public:
    int numOfNote;
    OneHund(int numOfNote){
        this->numOfNote = numOfNote;
    }
    void AprroveLeave(Withdrawal* l) override {
        int askedAmt = l->getAmount();
        int provNotes= askedAmt/100;
        int reminders= askedAmt%100;
        int givable = min(numOfNote, provNotes);

        if(reminders == 0){
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 100 Rupee Notes\n";
                numOfNote -= provNotes;
                return;
            }else if(givable > 0){
                cout<<givable <<" X 100 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount(askedAmt - givable*100);
            }
        }else{
            if(numOfNote >= provNotes){
                if(provNotes > 0) cout<<provNotes <<" X 100 Rupee Notes\n";
                numOfNote -= provNotes;
                l->setAmount(reminders);
            }else if(givable > 0){
                cout<<givable <<" X 100 Rupee Notes\n";
                numOfNote -= givable;
                l->setAmount((askedAmt - givable*100));
            }
        }

        if(nextApprover == nullptr){
            cout<<"can't make payment Amount: "<<l->getAmount()<<" \n";
            return;
        }
        nextApprover->AprroveLeave(l);
    }
};

class ATMCashDespenc{
    private:
    static ATMCashDespenc* instance;
    noteAmount* thu, *five, *one;
    
    ATMCashDespenc(){
        thu = new Thousand(2);
        five = new FiveHund(5);
        one = new OneHund(2);
        thu->setNext(five);
        five->setNext(one);
    }

    public:
    static ATMCashDespenc* getInstance(){
        if(instance == nullptr) instance = new ATMCashDespenc();
        return instance;
    }
    void SubmitForWithdrawal(Withdrawal* l){
        thu->AprroveLeave(l);
    }
    void makeWithdrawal(int days){
        Withdrawal w =  Withdrawal(days); // 
        SubmitForWithdrawal(&w);
    }
    
    void deleteInstance(){
        delete thu;
        delete five;
        delete one;
    }

    // ~ATMCashDespenc() { // destructur method
    //     delete thu;
    //     delete five;
    //     delete one;
    //     instance = nullptr; // Reset static instance
    //     cout << "ATM instance and notes deleted safely.\n";
    // }
};
ATMCashDespenc* ATMCashDespenc::instance = nullptr;

int main(){
    ATMCashDespenc* ATM = ATMCashDespenc::getInstance();
    ATM->makeWithdrawal(700);
    ATM->makeWithdrawal(2200);
    ATM->makeWithdrawal(300);
    ATM->makeWithdrawal(3800);

    ATM->deleteInstance();
    delete ATM;
    return 0;
}