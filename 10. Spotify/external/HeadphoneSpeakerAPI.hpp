#pragma once
#include <string>
#include <iostream>

using namespace std;

class HeadphoneSpeakerAPI {
    public:
    void playSoundViaHeadphoneAPI(const string& data){
        cout<< "[HeadphoneSpeakerAPI] Playing: " << data << "\n";
    }
};