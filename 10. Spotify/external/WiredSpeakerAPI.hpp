#pragma once
#include <string>
#include <iostream>

using namespace std;

class WiredSpeakerAPI {
    public:
    void playSoundViaWiredAPI(const string& data){
        cout<< "[WiredSpeakerAPI] Playing: " << data << "\n";
    }
};