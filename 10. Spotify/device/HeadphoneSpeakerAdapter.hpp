#pragma once
#include "IAudioOutputDevice.hpp"
#include "../models/Song.hpp"
#include "../external/HeadphoneSpeakerAPI.hpp"

using namespace std;

class HeadphoneSpeakerAdapter : public IAudioOutputDevice {
    private:
    HeadphoneSpeakerAPI* headphoneApi;
    public:
    HeadphoneSpeakerAdapter(HeadphoneSpeakerAPI* api){
        headphoneApi = api;
    }
    void playAudio(Song* song) override {
        string payload = song->getTitle() + " On Path " + song->getPath();
        headphoneApi->playSoundViaHeadphoneAPI(payload);
    }
};