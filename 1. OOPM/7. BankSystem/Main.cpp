// #include <vector>
// #include <iostream>
// #include <string>
// using namespace std;

// // Forward declaration so Bank can refer to Account*
// class Account;

// class Bank {
// private:
//     int totalAmount;
//     int totalAccounts;
//     // store pointers so Account can be an incomplete type here
//     vector<Account*> accs;

// public:
//     string bankName;

//     Bank(string bankName){
//         this->bankName = bankName;
//         totalAmount = 0;
//         totalAccounts = 0;
//     }

//     // accept pointer and store it
//     void createAcc(Account* acc){
//         accs.push_back(acc);
//         // optionally update counters, totals etc.
//         totalAccounts++;
//     }
// };

// class Customer {
// public:
//     string name;
//     int age;
//     Customer(string name, int age){
//         this->name = name;
//         this->age = age;
//     }
// };

// // Account still inherits Bank (as in your original design)
// class Account : public Customer, public Bank {
// private:
//     int balance;
//     int accNumber;

// public:
//     Account(int balance, int accNumber, Customer customer, Bank b)
//         : Customer(customer), Bank(b)
//     {
//         this->accNumber = accNumber;
//         this->balance = balance;
//     }

//     void Deposit(int val){
//         if(val > 0){
//             balance += val;
//         } else {
//             cout << "Invalid Amount: " << val << endl;
//         }
//     }

//     void Widro(int val){
//         if(val < balance){
//             balance -= val;
//         } else {
//             cout << "Insuficient Amount: " << val << endl;
//         }
//     }
// };

// int main(){
//     Customer c1("Rohit", 21);
//     Bank b1("SBI");
//     Account a1(500, 101, c1, b1);

//     cout << a1.name << endl;
//     return 0;
// }
































#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------
// Base Class: Bank
// -----------------------------------------
class Bank {
protected:
    string bankName;

public:
    Bank(string name) {
        bankName = name;
    }

    void showBank() {
        cout << "Bank: " << bankName << endl;
    }
};

// -----------------------------------------
// Derived Class: Account (IS-A Bank)
// -----------------------------------------
class Account : public Bank {
protected:
    int accNumber;
    int balance;

public:
    Account(string bankName, int accNumber, int balance): Bank(bankName) {
        this->accNumber = accNumber;
        this->balance = balance;
    }

    void deposit(int val) {
        if (val > 0) balance += val;
    }

    void withdraw(int val) {
        if (val <= balance) balance -= val;
    }

    void showAccount() {
        cout << "Account Number: " << accNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

// -----------------------------------------
// Derived Class: Customer (IS-A Account)
// -----------------------------------------
class Customer : public Account {
public:
    string name;
    int age;

    Customer(string name, int age,
             string bankName, int accNumber, int balance)
        : Account(bankName, accNumber, balance)
    {
        this->name = name;
        this->age = age;
    }

    void showCustomer() {
        cout << "Customer Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// -----------------------------------------
// Main
// -----------------------------------------
int main() {

    Customer c("Rohit", 21, "SBI", 101, 500);

    c.showCustomer();
    c.showAccount();
    c.showBank();

    return 0;
}
