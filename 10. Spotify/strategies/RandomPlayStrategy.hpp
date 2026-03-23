#pragma once
#include <iostream>
#include <stack>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"

using namespace std;

class RandomPlayStrategy : public PlayStrategy {
    private:
    Playlist* currPlaylist;
    vector<Song*> remainingSongs;
    stack<Song*> history;

    public:
    RandomPlayStrategy(){
        currPlaylist = nullptr;
        srand((unsigned)time(nullptr));
    }

    void setPlaylist(Playlist* playlist) override {
        currPlaylist = playlist;
        if(!currPlaylist || currPlaylist->getSize() == 0) return;

        remainingSongs = currPlaylist->getSongs();
        history = stack<Song*> ();
    }

    bool hasNext() override {
        return currPlaylist && !remainingSongs.empty();
    }

    Song* next() override{
        if(!currPlaylist || currPlaylist->getSize() == 0){
            throw runtime_error("no playList or empty playlist");
        }
        if(remainingSongs.empty()){
            throw runtime_error("no song left to play");
        }
        int index = rand() % remainingSongs.size();
        Song* selectedSong =  currPlaylist->getSongs()[index];

        swap(remainingSongs[index], remainingSongs.back());
        remainingSongs.pop_back();

        history.push(selectedSong);
        return selectedSong;
    }

    bool hasPrevious() override {
        return history.size() > 0;
    }

    Song* previous() override {
        if(history.empty()){
            throw runtime_error("no playList or empty playlist");
        }
        Song* song = history.top();
        history.pop();
        return song;
    }
};