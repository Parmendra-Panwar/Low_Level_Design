#include <iostream>
#include <stdexcept>
using namespace std;

// Custom exception class derived from std::runtime_error
class CustomRuntimeError : public runtime_error { // for being more meaningful 
public:
    CustomRuntimeError(const string& message) : runtime_error(message) {}
};

class Calculator {
public:
    double divide(int a, int b) {
        if (b == 0) {
            throw CustomRuntimeError("Division by zero error"); //CustomRuntime for catch check the catch
        }
        return static_cast<double>(a) / b;
    }
    
    void allocateLargeMemory(size_t size) {
        int* ptr = nullptr;
        try {
            ptr = new int[size];  // throw std::bad_alloc if size too large
            cout << "Memory allocation successful\n";
            delete[] ptr;
        }
        catch (bad_alloc& e) {
            throw "some error"; 
        }
    }
};

int main() {
    Calculator calc;

    try {
        double result = calc.divide(10, 0);  // triggers runtime error (division by zero)
        cout << "Result: " << result << endl; // not gonna print if error
    }
    catch (const CustomRuntimeError& e) { // check the line 16 you pass the message in CustomRuntimeError wrraper
        cerr << "Caught CustomRuntimeError: " << e.what() << endl;
    }
    catch (const bad_alloc& e) { // konse type ki error pe kya karna hai isliye bad alloc ye sab kiya
        cerr << "Caught bad_alloc: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Caught standard exception: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Caught unknown exception" << endl;
    }

    try {
        calc.allocateLargeMemory(1000000000000);  // might trigger bad_alloc runtime error
    }
    catch (const CustomRuntimeError& e) {
        cerr << "Caught CustomRuntimeError: " << e.what() << endl;
    }
    catch (const bad_alloc& e) {
        cerr << "Caught bad_alloc: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Caught standard exception: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Caught unknown exception" << endl;
    }

    return 0;
}
