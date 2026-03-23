#pragma once
#include "core/AudioEngine.hpp"
#include "models/Playlist.hpp"
#include "models/Song.hpp"
#include "strategies/PlayStrategy.hpp"
#include "enums/DeviceType.hpp"
#include "enums/PlayStrategyType.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/PlaylistManager.hpp"
#include "managers/StrategyManager.hpp"

using namespace std;

class MusicPlayerFacade{
    private:
    static MusicPlayerFacade* instance;
    AudioEngine* audioEngine;
    Playlist* loadedPlaylist;
    PlayStrategy* playStrategy;

    MusicPlayerFacade(){
        loadedPlaylist = nullptr;
        playStrategy = nullptr;
        audioEngine = new AudioEngine();
    }

    public:
    static MusicPlayerFacade* getInstance(){
        if(!instance) instance = new MusicPlayerFacade();
        return instance;
    }

    void connectDevice(DeviceType dt){
        DeviceManager::getInstance()->connect(dt);
    }

    void setPlayStrategy(PlayStrategyType st){
        playStrategy = StrategyManager::getInstance()->getStategy(st);
    }
    
    void loadPlaylist(const string& name){
        loadedPlaylist = PlaylistManager::getInstance()->getPlaylist(name);
        if(!playStrategy) throw runtime_error("No Play Strategy is Selected");

        playStrategy->setPlaylist(loadedPlaylist);
    }

    void playSong(Song* song){
        if(!DeviceManager::getInstance()->hasOutputDevice()){
            throw runtime_error("No audio device connected");
        }

        IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
        audioEngine->play(device, song); 
    }

    void pauseSong(Song* song){
        if(audioEngine->getCurrSongTitle() != song->getTitle()){
            throw runtime_error("this song is not running");
        }
        audioEngine->pause();
    }

    void playALlTracks(){
        if(!loadedPlaylist){
            throw runtime_error("No Playlist Loaded");
        }

        while(playStrategy->hasNext()){
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }

        cout<<"Completed Playlist: " << loadedPlaylist->getplaylistName()<< "\n";
    }

    void playNextTrack(){
        if(!loadedPlaylist)
        throw runtime_error("No playlistLoaded");
        
        if(playStrategy->hasNext()){
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        else{
            cout<<"Completed Playlist: " << loadedPlaylist->getplaylistName()<< "\n";
        }
    }

    void playPreviousTrack(){
        if(!loadedPlaylist)
        throw runtime_error("No playlistLoaded");
        
        if(playStrategy->hasPrevious()){
            Song* nextSong = playStrategy->previous();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        else{
            cout<<"Completed Playlist: " << loadedPlaylist->getplaylistName()<< "\n";
        }
    }

    void enqueuNext(Song* song){
        playStrategy->addToNext(song);
    }
};

MusicPlayerFacade* MusicPlayerFacade::instance = nullptr;