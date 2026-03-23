#pragma once
#include "../models/Song.hpp"
using namespace std;

class IAudioOutputDevice {
    public:
    virtual ~IAudioOutputDevice(){}
    virtual void playAudio(Song* song) = 0;
};