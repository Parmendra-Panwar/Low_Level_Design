#pragma once
#include <string>
#include <iostream>

using namespace std;

class BluetoothSpeakerAPI {
    public:
    void playSoundViaBluetoothAPI(const string& data){
        cout<< "[BluetoothSpaker] Playing: " << data << "\n";
    }
};