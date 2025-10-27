# Abstraction in C++

### Concept
**Abstraction** means **showing only the necessary details** to the user and **hiding the complex internal logic**.

It helps us **focus on what an object does** instead of **how it does it**.

---

### Real-life Example
When you drive a car, you press the accelerator — you don’t need to know how the engine works internally.

---

### Code Example

```cpp
// Abstract class (interface-like behavior)
class Car {
public:
    virtual void start() = 0; // Pure virtual function
};

// Concrete class that hides internal details
class Tesla : public Car {
public:
    void start() override {
        cout << "Tesla started silently using electric motor." << endl;
    }
};

int main() {
    Car* myCar = new Tesla();
    myCar->start();  // We only know it starts, not how
    delete myCar;
}
