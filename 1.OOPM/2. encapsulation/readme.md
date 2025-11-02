# Encapsulation in C++

### What is Encapsulation?
**Encapsulation** means **wrapping data (variables)** and **functions (methods)** that operate on that data **inside one unit — a class**.  
It ensures that data is **protected from direct access or modification** from outside the class.

In simple words:  
We keep data **secure** and only allow changes through **safe functions**.

**Goal:** To protect and control how data is accessed or modified.

---

### Access Modifiers in C++
Access modifiers decide **who can access** the members (variables or functions) of a class.

| Modifier | Accessible From | Common Use |
|-----------|------------------|-------------|
| **public** | From anywhere | Used for functions that can be called by anyone |
| **private** | Only inside the same class | Used for sensitive data that should be hidden |
| **protected** | Inside class + child classes | Used in inheritance scenarios |

### Code Example

```cpp
#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance;  // Hidden data (Encapsulation)

public:
    // Constructor
    BankAccount(double amount) {
        balance = amount;
    }

    // Setter - Controlled modification
    void setBalance(double amount) {
        if (amount >= 0)
            balance = amount;
        else
            cout << "Invalid amount!" << endl;
    }

    // Getter - Read-only access
    double getBalance() const {
        return balance;
    }

    // Behavior methods
    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance!" << endl;
    }
    ~BankAccount() {}// Destructor
};

int main() {
    BankAccount acc(1000);  // Object created

    acc.deposit(500);
    acc.withdraw(200);

    cout << "Current Balance: " << acc.getBalance() << endl;

    acc.setBalance(3000); // Valid update
    cout << "Updated Balance: " << acc.getBalance() << endl;

    acc.setBalance(-100); // Invalid update (blocked)
}
