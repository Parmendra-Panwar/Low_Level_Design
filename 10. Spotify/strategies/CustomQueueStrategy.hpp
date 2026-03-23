#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"

using namespace std;

class CustomPlayStrategy : public PlayStrategy {
    private:
    Playlist* currPlaylist;
    int currIndex;
    queue<Song*> nextQueue;
    stack<Song*> prevStack;

    Song* nextSequential(){
        if(currPlaylist->getSize() == 0)
        throw runtime_error("Playlist is empty");

        currIndex = currIndex + 1;
        return currPlaylist->getSongs()[currIndex];
    }

    Song* previousSequential(){
        if(currPlaylist->getSize() == 0)
        throw runtime_error("Playlist is empty");

        currIndex = currIndex  - 1;
        return currPlaylist->getSongs()[currIndex];
    }

    public:
    CustomPlayStrategy(){
        currPlaylist = nullptr;
        currIndex = -1;
    }

    void setPlaylist(Playlist* playlist) override {
        currPlaylist = playlist;
        currIndex = -1;
        while(!nextQueue.empty()){
            nextQueue.pop();
        }
        while(!prevStack.empty())
        prevStack.pop();    
    }

    bool hasNext() override {
        return (currIndex + 1 < currPlaylist->getSize());
    }

    Song* next() override{
        if(!currPlaylist || currPlaylist->getSize() == 0){
            throw runtime_error("no playList or empty playlist");
        }
        if(!nextQueue.empty()){
            Song* song = nextQueue.front();
            nextQueue.pop();
            prevStack.push(song);

            auto& list = currPlaylist->getSongs();
            for(int i=0; i<(int)list.size(); ++i){
                if(list[i] == song){
                    currIndex = i;
                    break;
                }
            }
            return song;
        }
        return nextSequential();
    }

    bool hasPrevious() override {
        return (currIndex - 1 > 0);
    }

    Song* previous() override {
        if(!currPlaylist || currPlaylist->getSize() == 0){
            throw runtime_error("no playList or empty playlist");
        }
        if(!nextQueue.empty()){
            Song* song = nextQueue.front();
            nextQueue.pop();
            prevStack.push(song);

            auto& list = currPlaylist->getSongs();
            for(int i=0; i<(int)list.size(); ++i){
                if(list[i] == song){
                    currIndex = i;
                    break;
                }
            }
            return song;
        }
        return previousSequential();
    }

    void addToNext(Song* song) override {
        if(!song) throw runtime_error("Cannot enueue null song");

        nextQueue.push(song);
    }
};