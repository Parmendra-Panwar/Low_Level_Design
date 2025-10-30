## Current Focus: Object-Oriented Programming (OOP)
Before going into system-level design, it’s important to master the basics of OOP — the foundation of LLD.

---

## 🧩 What’s Covered

| Concept | Description | Folder |
|----------|--------------|--------|
| **Class & Object** | Blueprint and real-world instance in code |  |
| **Abstraction** | Hiding complex details and showing only essentials | `/abstraction/` |
| **Encapsulation** | Binding data and methods while controlling access | `/encapsulation/` |
| **Inheritance** | Reusing and extending code from existing classes | `/inheritance/` |
| **Polymorphism** | Same function behaving differently based on context | `/polymorphism/` |

---

## 🧠 Quick Recap

### 🔹 Class & Object Example

```cpp

class Car {
public:
    string brand;
    void drive() {
        cout << brand << " is driving..." << endl;
    }
};

int main() {
    Car c1;
    c1.brand = "Tesla";
    c1.drive();
}