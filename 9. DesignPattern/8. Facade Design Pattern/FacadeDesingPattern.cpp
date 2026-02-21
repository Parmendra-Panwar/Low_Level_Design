// complex system connection to ease by an interface
#include <iostream>
using namespace std;

class PowerSupply {
public:
    void providePower(){
        cout<< "Power Supply : Providing power..." <<endl;
    }
};
class CoolingSystem {
public:
    void startFans(){
        cout<< "Cooling System : Providing cooling..." <<endl;
    }
};
class CPU {
public:
    void initialize(){
        cout<< "CPU : Initialization..." <<endl;
    }
};
class Memory {
public:
    void selfTest(){
        cout<< "Memory: self Test Passed..." <<endl;
    }
};
class HardDrive {
public:
    void SpinUp(){
        cout<< "Hard Drive: Spinning Up..." <<endl;
    }
};
class BIOS {
public:
    void boot(CPU& cpu, Memory& memory){
        cout<< "BIOS: Booting CPU and Memory checks..." <<endl;
        cpu.initialize();
        memory.selfTest();
    }
};

class OperatingSystem {
public: 
    void load(){
        cout<< "Operating System: Loading into memory..."<<endl;
    }
};

class Facade {
private:
    PowerSupply powerSupply;
    CoolingSystem coolingSystem;
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;
    BIOS bios;
    OperatingSystem os;

public:
    void startComputer(){
        cout<<"----- Starting Computer -----"<<endl;
        powerSupply.providePower();
        coolingSystem.startFans();
        bios.boot(cpu, memory);
        hardDrive.SpinUp();
        os.load();
        cout<<"----- BootUp Successfully -----"<<endl;
    }
};

int main(){
    Facade computer;
    computer.startComputer();

    return 0;
}