#include <iostream>
using namespace std;

class Account{
    public:
    int balance;
    Account(int balance){
        this->balance = balance;
    }

    void addMoney(int m){
        if(m > 0){
            balance+=m;
            cout<<"Your amount: "<<m<<"$ is added Successfully\n";
        }else{
            throw "Please add a valid Amount\n";
        }
    }
    void takeMoney(int m){
        if(m>balance){
            throw "balance not enough\n";
        } // throw karne ke baad ka code agar throw hua to
          // nahi chalega

        balance-=m;
        cout<<"Take your amount: "<<m<<"$\n";
    }
};

int main(){
    Account* a1 = new Account(1000);
    // try ek block of code hai jo ki exception phek sakta hai
    try{
        a1->addMoney(0);
        a1->addMoney(100); // ab ye nahi chalega kyuki ?
                           // exception to aa rakha hai already
        a1->addMoney(0);
    }catch(const char*e){ // ye try ke exception ko catch karega
        cout<<"Exception Occured: "<<e<<endl;
    }
    cout<<"hello"<<endl;// but ye line chalega proper

    return 0;
}












































// #include <iostream>
// #include <stdexcept>
// using namespace std;

// // Custom exception class derived from std::runtime_error
// class CustomRuntimeError : public runtime_error {
// public:
//     CustomRuntimeError(const string& message) : runtime_error(message) {}
// };

// class Calculator {
// public:
//     // Function to divide two numbers - throws runtime error on division by zero
//     double divide(int a, int b) {
//         if (b == 0) {
//             throw CustomRuntimeError("Division by zero error");
//         }
//         return static_cast<double>(a) / b;
//     }
    
//     // Function that attempts a memory allocation - throws bad_alloc on allocation failure
//     void allocateLargeMemory(size_t size) {
//         int* ptr = nullptr;
//         try {
//             ptr = new int[size];  // Could throw std::bad_alloc if size too large
//             cout << "Memory allocation successful\n";
//             delete[] ptr;
//         }
//         catch (bad_alloc& e) {
//             throw;  // rethrow to caller
//         }
//     }
// };

// int main() {
//     // Uncommenting the following line will cause a compile-time error (missing semicolon)
//     // int number = 10

//     Calculator calc;

//     try {
//         double result = calc.divide(10, 0);  // triggers runtime error (division by zero)
//         cout << "Result: " << result << endl;

//         calc.allocateLargeMemory(1000000000000);  // might trigger bad_alloc runtime error
//     }
//     catch (const CustomRuntimeError& e) {
//         cerr << "Caught CustomRuntimeError: " << e.what() << endl;
//     }
//     catch (const bad_alloc& e) {
//         cerr << "Caught bad_alloc: " << e.what() << endl;
//     }
//     catch (const exception& e) {
//         cerr << "Caught standard exception: " << e.what() << endl;
//     }
//     catch (...) {
//         cerr << "Caught unknown exception" << endl;
//     }

//     return 0;
// }
