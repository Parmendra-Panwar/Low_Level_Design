#include <iostream>
using namespace std;

// ====== STRATEGY INTERFACES ======

// Walking behavior interface
class WalkableRobot {
  public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {} // virtual destructor for cleanup
};

// Concrete walking strategies
class NormalWalk : public WalkableRobot {
  public:
    void walk() override {
      cout << "Normal Walking..." << endl;
    }
};
class NoWalk : public WalkableRobot {
  public:
    void walk() override {
      cout << "I can't walk." << endl;
    }
};

// Talking behavior interface
class TalkableRobot {
  public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// Concrete talking strategies
class NormalTalk : public TalkableRobot {
  public:
    void talk() override {
      cout << "Normal Talking..." << endl;
    }
};
class NoTalk : public TalkableRobot {
  public:
    void talk() override {
      cout << "I can't talk." << endl;
    }
};

// ====== BASE ROBOT CLASS (Context) ======
class Robot {
  protected:
    WalkableRobot* walkableRobot; // Strategy for walking
    TalkableRobot* talkableRobot; // Strategy for talking

  public:
    // Inject behavior strategies via constructor
    Robot(WalkableRobot* wr, TalkableRobot* tr)
        : walkableRobot(wr), talkableRobot(tr) {}

    // Delegate behavior to strategy objects
    void walk()  { walkableRobot->walk(); }
    void talk()  { talkableRobot->talk(); }

    virtual void projection() = 0; // Unique behavior per robot type

    // Virtual destructor ensures safe deletion through base pointer
    virtual ~Robot() {
      delete walkableRobot;
      delete talkableRobot;
    }
};

// ====== CONCRETE ROBOTS ======
class Type1Robot : public Robot {
  public:
    // Properly call base class constructor
    Type1Robot(WalkableRobot* wr, TalkableRobot* tr)
      : Robot(wr, tr) {}

    void projection() override {
      cout << "Type1 Robot Projection" << endl;
    }
};

class Type2Robot : public Robot {
  public:
    Type2Robot(): Robot(new NormalWalk(), new NoTalk()){}    

    void projection() override {
      cout << "Type2 Robot Projection" << endl;
    }
};

// ====== CLIENT CODE ======
int main() {
  Robot* robot1 = new Type1Robot(new NormalWalk(), new NormalTalk());
  robot1->walk();        // Delegates to NormalWalk
  robot1->talk();        // Delegates to NormalTalk
  robot1->projection();  // Type1-specific
  delete robot1;         // Automatically cleans up strategies

  cout << endl;

  Robot* robot2 = new Type2Robot();
  robot2->walk();        // Delegates to NoWalk
  robot2->talk();        // Delegates to NormalTalk
  robot2->projection();  // Type2-specific
  delete robot2;

  return 0;
}
