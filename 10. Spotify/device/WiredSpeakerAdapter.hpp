#pragma once
#include "IAudioOutputDevice.hpp"
#include "../models/Song.hpp"
#include "../external/WiredSpeakerAPI.hpp"

using namespace std;

class WiredSpeakerAdapter : public IAudioOutputDevice {
    private:
    WiredSpeakerAPI* wiredApi;
    public:
    WiredSpeakerAdapter(WiredSpeakerAPI* api){
        wiredApi = api;
    }
    void playAudio(Song* song) override {
        string payload = song->getTitle() + " On Path " + song->getPath();
        wiredApi->playSoundViaWiredAPI(payload);
    }
};