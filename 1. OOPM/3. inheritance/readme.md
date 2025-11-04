# Inheritance in C++

### What is Inheritance?
**Inheritance** is an OOP concept where one class (child or derived class) **inherits properties and behaviors** from another class (parent or base class).  
It helps in **reusing code**, **avoiding duplication**, and **creating logical hierarchies**.

In simple words:  
Inheritance means **“using old code to build new code”**.

---

### Why Use Inheritance?
- Promotes **code reusability**
- Helps in **extending functionality**
- Makes code **organized and maintainable**

---

### Basic Syntax

```cpp
class Base {
   // base class members
};

class Derived : access_modifier Base {
   // derived class members
};


##  Example: Simple Inheritance
### 1️⃣ Single Inheritance
A single child inherits from a single parent.
```cpp
class Parent {
public:
    void showParent() { cout << "Parent class\n"; }
};

class Child : public Parent {
public:
    void showChild() { cout << "Child class\n"; }
};

int main() {
    Child obj;
    obj.showParent();
    obj.showChild();
}


### 2️⃣ Multilevel Inheritance
Inheritance through multiple levels (like a chain).
```cpp
class GrandParent {
public:
    void func1() { cout << "GrandParent class\n"; }
};

class Parent : public GrandParent {
public:
    void func2() { cout << "Parent class\n"; }
};

class Child : public Parent {
public:
    void func3() { cout << "Child class\n"; }
};

int main() {
    Child obj;
    obj.func1();
    obj.func2();
    obj.func3();
}


### 3️⃣ Multiple Inheritance
A single child inherits from multiple parents.
```cpp
class A {
public:
    void funcA() { cout << "Class A\n"; }
};

class B {
public:
    void funcB() { cout << "Class B\n"; }
};

class C : public A, public B {
public:
    void funcC() { cout << "Class C\n"; }
};

int main() {
    C obj;
    obj.funcA();
    obj.funcB();
    obj.funcC();
}

### 4️⃣ Hierarchical Inheritance
Multiple child classes inherit from a single parent.
```cpp
class Vehicle {
public:
    void engine() { cout << "Engine started\n"; }
};

class Car : public Vehicle {
public:
    void wheels() { cout << "Car has 4 wheels\n"; }
};

class Bike : public Vehicle {
public:
    void type() { cout << "Bike is two-wheeler\n"; }
};

int main() {
    Car c;
    Bike b;

    c.engine();
    c.wheels();

    b.engine();
    b.type();
}


### 5️⃣ Hybrid (or Virtual) Inheritance
Combination of multiple and multilevel inheritance.
It can cause the diamond problem, where a child inherits the same base class twice.

To solve this, we use the virtual keyword.

```cpp
class A {
public:
    void show() { cout << "Class A\n"; }
};

class B : virtual public A {};
class C : virtual public A {};

class D : public B, public C {};

int main() {
    D obj;
    obj.show(); // No ambiguity due to virtual inheritance
}
