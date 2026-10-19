#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cloneable {
public:
    virtual Cloneable* clone() const = 0;
    virtual ~Cloneable() {}
};

class NPC : public Cloneable {
public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(const string& name, int health, int attack, int defense) {
        this->name = name; 
        this->health = health; 
        this->attack = attack; 
        this->defense = defense;
        cout << "Setting up template NPC '" << name << "'\n";
    }

    NPC(const NPC& other) {
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;
        cout << "Cloning NPC '" << name << "'\n";
    }

    Cloneable* clone() const override {
        return new NPC(*this);
    }

    void describe() {
        cout << "NPC " << name  << " [HP=" << health  << " ATK=" << attack 
             << " DEF=" << defense << "]\n";
    }

    void setName(const string& n) { 
        name = n;
    }
    void setHealth(int h) { 
        health = h;
    }
    void setAttack(int a) {
         attack = a; 
    }
    void setDefense(int d){ 
        defense = d;
    }
};

int main() {
    NPC* alien = new NPC("Alien", 30, 5, 2);

    NPC* alienCopied1 = dynamic_cast<NPC*>(alien->clone());
    alienCopied1->describe();

    NPC* alienCopied2 = dynamic_cast<NPC*>(alien->clone());
    alienCopied2->setName("Powerful Alien");
    alienCopied2->setHealth(50);
    alienCopied2->describe();

    delete alien;
    delete alienCopied1;
    delete alienCopied2;
}

        