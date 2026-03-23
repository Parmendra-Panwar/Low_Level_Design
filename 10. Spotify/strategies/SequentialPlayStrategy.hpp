#pragma once
#include <iostream>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"

using namespace std;

class SequentialPlayStrategy : public PlayStrategy {
    private:
    Playlist* currPlaylist;
    int currIndex;
    public:
    SequentialPlayStrategy(){
        currPlaylist = nullptr;
        currIndex = -1;
    }

    void setPlaylist(Playlist* playlist) override {
        currPlaylist = playlist;
        currIndex = -1;
    }

    bool hasNext() override {
        return ((currIndex + 1) < currPlaylist->getSize());
    }

    Song* next() override{
        if(!currPlaylist || currPlaylist->getSize() == 0){
            throw runtime_error("no playList or empty playlist");
        }

        currIndex = currIndex +1;
        return currPlaylist->getSongs()[currIndex];
    }

    bool hasPrevious() override {
        return (currIndex-1 > 0) ;
    }

    Song* previous() override {
        if(!currPlaylist || currPlaylist->getSize() == 0){
            throw runtime_error("no playList or empty playlist");
        }
        currIndex = currIndex - 1;
        return currPlaylist->getSongs()[currIndex];
    }
};