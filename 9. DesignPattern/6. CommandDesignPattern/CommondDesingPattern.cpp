#include <iostream>
#include <vector>

using namespace std;

class ICommand{
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual ~ICommand() {};
};

class Light{
    public:
    void on() {
        cout<<"LIGHT ON"<<endl;
    }
    void off() {
        cout<<"LIGHT OFF"<<endl;
    }
};
class Fan{
    public:
    void on() {
        cout<<"FAN ON"<<endl;
    }
    void off() {
        cout<<"FAN OFF"<<endl;
    }
};

class LightCommand: public ICommand{
    private:
        Light* light;
    public:

    LightCommand(Light* l){
        light = l;
    }
    void execute(){
        light->on();
    }
    void undo(){
        light->off();
    }
};
class FanCommand: public ICommand{
    private:
        Fan* fan;
    public:

    FanCommand(Fan* l){
        fan = l;
    }
    void execute(){
        fan->on();
    }
    void undo(){
        fan->off();
    }
};

class RemoteController{
    private:
        static const int numButtons = 3;
        ICommand *buttons[numButtons];
        bool buttonPressed[numButtons];
    public:
    RemoteController(){
        for(int i=0; i<numButtons; i++){
            buttons[i] = nullptr;
            buttonPressed[i] = false;
        }
    }

    void setCommand(int idx, ICommand* cmd){
        if(idx >= 0 && idx < numButtons){
            if(buttons[idx]!=nullptr)
                delete buttons[idx];
            buttons[idx] = cmd;
            buttonPressed[idx] = false; 
        }
        
    }

    void pressButton(int idx){
        if(idx >= 0 && idx < numButtons && buttons[idx]!=nullptr){
            if(buttonPressed[idx] == false){
                buttons[idx]->execute();
            }else{
                buttons[idx]->undo();
            }
                
            buttonPressed[idx] = !buttonPressed[idx]; 
        }else{
            cout<<"press a valid button"<<endl;
        }
    }

    ~RemoteController(){
        for(int i=0; i<numButtons; i++){
            if(buttons[i] != NULL){
                delete buttons[i];
            }
        }
    } 
};

int main(){
    Light* roomLight = new Light();
    Fan* roomFan = new Fan();
    RemoteController* remote = new RemoteController();

    remote->setCommand(0, new LightCommand(roomLight));
    remote->setCommand(1, new FanCommand(roomFan));

    remote->pressButton(0);
    remote->pressButton(0);
    
    remote->pressButton(1);
    remote->pressButton(1);

    delete remote;
    delete roomLight;
    delete roomFan;
    return 0;
}
