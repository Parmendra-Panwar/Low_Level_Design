# Exception Handling 

## What is an Exception?
It is a mechanism to handle errors or unexpected events during program execution.
When an exception occurs, it is "thrown" and can be "caught" by an exception handler to control program flow and perform cleanup.

## what is runtime and compile time
### Compile Time:
- It is the period during which the source code is translated into executable machine code by the compiler.
- Compile-time errors happen during this phase and are mainly syntax or semantic errors (like missing semicolons, undeclared variables).
- The program cannot run unless all compile-time errors are fixed.

Example compile-time error: Missing semicolon in C++.

### Runtime:
- It is the period when the compiled executable program is actually running on the machine.
- Runtime errors occur during this execution and are usually due to unexpected conditions like division by zero, out-of-bounds array access, or null pointer dereferences.

These errors cannot be detected by the compiler since they depend on program inputs or state at runtime.



| Exception Type            | Description                                          |
| ------------------------- | ---------------------------------------------------- |
| std::exception            | Base class for all standard exceptions               |
| std::logic_error          | Program logic-related errors detected before runtime |
| std::domain_error         | Invalid domain values                                |
| std::invalid_argument     | Invalid function arguments                           |
| std::length_error         | Exceeding maximum size constraints                   |
| std::out_of_range         | Access beyond valid range                            |
| std::runtime_error        | Errors detected at runtime                           |
| std::range_error          | Internal range errors                                |
| std::overflow_error       | Arithmetic overflow                                  |
| std::underflow_error      | Arithmetic underflow                                 |
| std::system_error         | System API errors                                    |
| std::ios_base::failure    | I/O stream failures                                  |
| std::bad_alloc            | Memory allocation failure                            |
| std::bad_array_new_length | Invalid array lengths in allocation                  |
| std::bad_cast             | Invalid dynamic cast                                 |
| std::bad_typeid           | Invalid use of typeid                                |
| std::bad_exception        | Unexpected exception handling                        |
| std::bad_function_call    | Calling an empty function wrapper                    |
| std::bad_weak_ptr         | Invalid weak pointer usage                           |

### Base Exception Class:
std::exception: The base class for all standard C++ exceptions. It provides the virtual function what() that returns an explanatory string.

### Logic Errors (Detectable before runtime, typically errors in program logic):
std::logic_error: Base class for logic errors.

- std::domain_error: For domain errors like invalid mathematical domain values (e.g., sqrt of a negative number).
- std::invalid_argument: When an invalid argument is passed to a function.
- std::length_error: When an operation tries to create a string or container larger than its maximum size.
- std::out_of_range: For accessing elements outside the valid range (e.g., vector index out of range).

### Runtime Errors (Detected during program execution):
std::runtime_error: Base class for runtime errors.

- std::range_error: Errors in internal computations that result in out-of-range values.
- std::overflow_error: When an arithmetic overflow occurs.
- std::underflow_error: When an arithmetic underflow occurs.
- std::regex_error: Errors from the regular expression library.
- std::system_error: Errors related to system API failures.
- std::ios_base::failure: Input/output stream errors.

### Memory Allocation Errors:
std::bad_alloc: Thrown when memory allocation using new fails.
std::bad_array_new_length: Thrown when trying to allocate an invalid (usually too large) array size.

### Dynamic Type and Cast Errors:
std::bad_cast: Thrown by dynamic_cast when an invalid cast is performed.
std::bad_typeid: Thrown by typeid when applied to a null pointer to polymorphic type.

### Function and Pointer Errors:
std::bad_function_call: Thrown by an empty std::function object call.
std::bad_weak_ptr: Occurs when constructing a shared pointer from an invalid weak pointer.

### Special Cases:
std::bad_exception: Used to handle unexpected exceptions.
std::nested_exception: Supports chained/nested exceptions.


## Most Importently 
### Runtime Exception (std::runtime_error):

- Represents errors detectable only when the program runs (e.g., logic errors).
- Example: trying to open a file that doesn’t exist or a division by zero.
- It inherits from std::exception and carries a message describing the problem.

### std::bad_alloc Exception:

- Thrown by the C++ memory allocation system when new fails to allocate memory.
- This typically happens if the system runs out of memory.
- It signals memory allocation failure, and it’s a subclass of std::exception.


```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

// Custom exception class derived from std::runtime_error
class CustomRuntimeError : public runtime_error {
public:
    CustomRuntimeError(const string& message) : runtime_error(message) {}
};

class Calculator {
public:
    // Function to divide two numbers - throws runtime error on division by zero
    double divide(int a, int b) {
        if (b == 0) {
            throw CustomRuntimeError("Division by zero error");
        }
        return static_cast<double>(a) / b;
    }
    
    // Function that attempts a memory allocation - throws bad_alloc on allocation failure
    void allocateLargeMemory(size_t size) {
        int* ptr = nullptr;
        try {
            ptr = new int[size];  // Could throw std::bad_alloc if size too large
            cout << "Memory allocation successful\n";
            delete[] ptr;
        }
        catch (bad_alloc& e) {
            throw;  // rethrow to caller
        }
    }
};

int main() {
    // Uncommenting the following line will cause a compile-time error (missing semicolon)
    // int number = 10

    Calculator calc;

    try {
        double result = calc.divide(10, 0);  // triggers runtime error (division by zero)
        cout << "Result: " << result << endl;

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

---

