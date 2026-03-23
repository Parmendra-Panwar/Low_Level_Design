#pragma once
#include <iostream>
#include <map>
#include <string>
#include "../models/Playlist.hpp"

using namespace std;

class PlaylistManager {
    private: 
    static PlaylistManager* instance;
    map<string, Playlist*> playlists;
    PlaylistManager(){}
    public:
    static PlaylistManager* getInstance(){
        if(instance == nullptr){
            instance = new PlaylistManager();
        }
        return instance;
    }
    void createPlaylist(const string& name){
        if(playlists.count(name)){
            throw runtime_error("Playlist Already Exist");
        }
        playlists[name] = new Playlist(name);
    }

    void createPlaylist(const string& playlistName, Song* song){
        if(!playlists.count(playlistName)){
            throw runtime_error("Playlist not Exist");
        }
        playlists[playlistName]->addSongToPlaylist(song);
    }
    Playlist* getPlaylist(const string& name){
        if(!playlists.count(name)){
            throw runtime_error("Playlist Not Exist");
        }
        return playlists[name];
    }

};

PlaylistManager* PlaylistManager::instance = nullptr;