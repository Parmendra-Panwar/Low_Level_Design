#pragma once
#include "managers/PlaylistManager.hpp"
#include "MusicPlayerFacade.hpp"

using namespace std;

class MusicPlayerApplication{
    private:
    static MusicPlayerApplication* instance;
    vector<Song*> songLibrary;
    MusicPlayerApplication(){}

    public: 
    static MusicPlayerApplication* getInstance(){
        if(!instance) instance = new MusicPlayerApplication();
        return instance;
    }

    void createSongInLibrary(const string& title, const string& path){
        Song* newSong = new Song(title, path);
        songLibrary.push_back(newSong);
    }

    Song* findSongByTitle(const string& title){
        for(Song* s : songLibrary){
            if(s->getTitle() == title) return s;
        }
        return nullptr;
    }

    void createPlaylist(const string& playlistName){
        PlaylistManager::getInstance()->createPlaylist(playlistName);
    }
    void addSongToPlaylist(const string& pl, const string& st){
        Song* song = findSongByTitle(st);
        if(!song)
        throw runtime_error("no song exist");
        PlaylistManager::getInstance()->addSongToPlaylist(pl, song);
    }

    void connectAudioDevice(DeviceType dt){
        MusicPlayerFacade::getInstance()->connectDevice(dt);
    }
    void selectPlayStrategy(PlayStrategyType strategyType) {
        MusicPlayerFacade::getInstance()->setPlayStrategy(strategyType);
    }
    void loadPlaylist(const string& pl){
        MusicPlayerFacade::getInstance()->loadPlaylist(pl);
    }
    void playSingleSong(const string& st){
        Song* song = findSongByTitle(st);
        if(!song) throw runtime_error("Song not Found");

        MusicPlayerFacade::getInstance()->playSong(song);
    }

    void pauseCurrentSong(const string& songtitle){
        Song* song = findSongByTitle(songtitle);
        if(!song) throw runtime_error("Song not Found");
        MusicPlayerFacade::getInstance()->pauseSong(song);
    }
    void playAllTracksInPlaylist(){
        MusicPlayerFacade::getInstance()->playALlTracks();
    }
    void playPreviousTrackInPlaylist(){
        MusicPlayerFacade::getInstance()->playPreviousTrack();
    }
    void queueSongNext(const string& songT){
        Song* song = findSongByTitle(songT);
        if(!song) throw runtime_error("Song not found");

        MusicPlayerFacade::getInstance()->enqueuNext(song);
    }
};

MusicPlayerApplication* MusicPlayerApplication::instance = nullptr;