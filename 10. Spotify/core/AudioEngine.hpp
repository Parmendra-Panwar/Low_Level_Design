#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include <string>
#include <iostream>

using namespace std;

class AudioEngine {
    private:
    Song* currSong;
    bool songIsPaused;
    public:
    AudioEngine(){
        currSong = nullptr;
        songIsPaused = false;
    }
    string getCurrSongTitle() const {
        if(currSong){
            return currSong->getTitle();
        }
        return "";
    }
    bool isPaused() const {
        return songIsPaused;
    }
    void play(IAudioOutputDevice* aod, Song* song){
        if(song == nullptr) throw runtime_error("Song is NULL");

        if(songIsPaused && song == currSong){
            songIsPaused = false;
            cout<< "Resuming song: "<<song->getTitle() << "\n";
            aod->playAudio(song);
            return;
        }
        currSong = song;
        songIsPaused = false;
        cout<<"Playing Song: "<< song->getTitle() << "\n";
        aod->playAudio(song);
    }

    void pause(){
        if(currSong == nullptr){
            throw runtime_error("No Song is currently playing");
        }
        if(songIsPaused){
            throw runtime_error("Song is already Paused");
        }

        songIsPaused = true;
        cout<< "Pausing Song: " << currSong->getTitle() << "\n";
    }
};
