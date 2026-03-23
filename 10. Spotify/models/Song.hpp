#pragma once
#include <string>
#include <iostream>

using namespace std;

class Song {
    private:
    string title;
    string path;
    public:
    Song(string t, string f){
        title = t;
        path = f;
    }
    string getTitle(){
        return title;
    }
    string getPath(){
        return path;
    }
};