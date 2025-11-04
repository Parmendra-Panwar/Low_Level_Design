#include <iostream>
using namespace std;

int main() {
    // Compile-time error example: Uncomment to see error
    // int a = 10
    // Missing semicolon above will cause compile-time error

    try {
        int x = 10;
        int y = 0;
        if (y == 0) {
            throw runtime_error("Division by zero error");
        }
        cout << x / y << endl;  // This line causes a runtime error (if exception not thrown)
    }
    catch (const runtime_error& e) {
        cerr << "Caught a runtime error: " << e.what() << endl;
    }
    return 0;
}
