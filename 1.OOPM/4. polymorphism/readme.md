# Polymorphism in C++

## What is Polymorphism?
Polymorphism means many forms.  
In C++, polymorphism allows the same function name or operator to behave differently depending on the object or data type it acts upon.  

It helps achieve flexibility, code reusability, and dynamic behavior during runtime.  

In simple words:  
Polymorphism means “one interface, many implementations.”

---

## Why Use Polymorphism?
- Helps in code flexibility and extensibility  
- Promotes reusability and maintainability  
- Enables runtime decision-making  
- Allows generic programming through overloading and overriding  

---

## Types of Polymorphism in C++
Polymorphism in C++ is mainly of two types:
1. Compile-time Polymorphism (Static Binding)  
2. Runtime Polymorphism (Dynamic Binding)  

---

## 1️⃣ Compile-time (Static) Polymorphism
This type of polymorphism is resolved at compile time.  
It includes:
- Function Overloading  
- Operator Overloading  

---

### Function Overloading
Multiple functions with the same name but different parameters.

```cpp
#include <iostream>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    Calculator calc;
    cout << calc.add(5, 10) << endl;
    cout << calc.add(2.5, 3.7) << endl;
    cout << calc.add(1, 2, 3) << endl;
}
```

---

### Operator Overloading
Redefining the behavior of an operator for user-defined types.

```cpp
#include <iostream>
using namespace std;

class Complex {
    int real, imag;
public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    // Overload '+' operator
    Complex operator + (const Complex& obj) {
        return Complex(real + obj.real, imag + obj.imag);
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4), c2(2, 5);
    Complex c3 = c1 + c2;   // Calls overloaded operator
    c3.display();
}
```

---

## 2️⃣ Runtime (Dynamic) Polymorphism
This type is resolved at runtime using **virtual functions** and **inheritance**.  
It lets the base class pointer call methods of derived classes dynamically.

---

### Example: Virtual Functions

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() {       // Virtual function
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks" << endl;
    }
};

class Cat : public Animal {
public:
    void sound() override {
        cout << "Cat meows" << endl;
    }
};

int main() {
    Animal* a;       // Base class pointer

    Dog d;
    Cat c;

    a = &d;
    a->sound();      // Calls Dog’s sound()

    a = &c;
    a->sound();      // Calls Cat’s sound()
}
```

---

### Virtual Function Rules
- Declared in the base class using the keyword `virtual`.  
- Can be overridden in the derived class.  
- Runtime binding happens when accessed via a base class pointer.  
- Destructors can also be virtual to ensure proper cleanup.  

---

### Pure Virtual Functions and Abstract Classes
If a class has a function declared as **pure virtual**, it becomes an **abstract class**.

```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;   // Pure virtual function
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

int main() {
    Shape* s = new Circle();
    s->draw();
    delete s;
}
```

**Key points:**
- Abstract classes cannot be instantiated.  
- They act as interfaces for derived classes.  

---

### Virtual Destructors
Used to ensure the proper destruction of derived objects via base class pointers.

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() {
        cout << "Base Destructor\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived Destructor\n";
    }
};

int main() {
    Base* b = new Derived();
    delete b;   // Ensures Derived’s destructor is called first
}
```

---

## Key Differences Between Static and Dynamic Polymorphism  

| Feature | Static Polymorphism | Dynamic Polymorphism |
|----------|--------------------|----------------------|
| Resolution Time | Compile Time | Runtime |
| Techniques Used | Function & Operator Overloading | Virtual Functions & Function Overriding |
| Speed | Faster | Slower (due to runtime binding) |
| Flexibility | Less | More |
| Memory Usage | Fixed | Uses vtable (slightly more) |
```