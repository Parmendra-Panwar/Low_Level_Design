#pragma once
#include <iostream>
#include "../device/IAudioOutputDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../factories/DeviceFactory.hpp"

using namespace std;

class DeviceManager {
    private: 
    static DeviceManager* instance;
    IAudioOutputDevice* currentOutputDevice;
    DeviceManager(){
        currentOutputDevice = nullptr;
    }
    public:
    static DeviceManager* getInstance(){
        if(instance == nullptr){
            instance = new DeviceManager();
        }
        return instance;
    }
    void connect(DeviceType deviceType){
        if(currentOutputDevice){
            delete currentOutputDevice;
        }
        currentOutputDevice = DeviceFactory::createDevice(deviceType);

        switch(deviceType){
            case DeviceType::BLUETOOTH:
            cout <<"Bluetooth Device Connected \n";
            break;
            case DeviceType::WIRED:
            cout <<"WIRED Device Connected \n";
            break;
            case DeviceType::HEADPHONE:
            cout <<"HEADPHONE Device Connected \n";
        }
    }

    IAudioOutputDevice* getOutputDevice(){
        if(!currentOutputDevice){
            throw runtime_error("No output device is connected");
        }
        return currentOutputDevice;
    }

    bool hasOutputDevice(){
        return currentOutputDevice != nullptr;
    }
};

DeviceManager* DeviceManager::instance = nullptr;