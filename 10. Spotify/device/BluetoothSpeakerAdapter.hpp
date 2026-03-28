#pragma once
#include "IAudioOutputDevice.hpp"
#include "../models/Song.hpp"
#include "../external/BluetoothSpeakerApi.hpp"

using namespace std;

class BluetoothSpeakerAdapter : public IAudioOutputDevice {
    private:
    BluetoothSpeakerAPI* bluetoothApi;
    public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* api){
        bluetoothApi = api;
    }
    void playAudio(Song* song) override {
        string payload = song->getTitle() + " On Path " + song->getPath();
        bluetoothApi->playSoundViaBluetoothAPI(payload);
    }
};