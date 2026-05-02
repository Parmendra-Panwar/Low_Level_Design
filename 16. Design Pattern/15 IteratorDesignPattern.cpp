#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// abstract class Iterator
template<typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// abstract class Iterable
template<typename T>
class Iterable {
public:
    virtual ~Iterable() {}
    virtual Iterator<T>* getIterator() = 0;
};

// concreat class Linked List
class LinkedList : public Iterable<int>{
public:
    int data;
    LinkedList* next;
    LinkedList(int data) {
        this->data = data;
        this->next = nullptr;
    }

    Iterator<int>* getIterator() override;  
};

// Song Class For Playlist
class Song{
public:
    string title;
    string artist;
    Song(string title, string artist){
        this->title = title;
        this->artist = artist;
    }
};

class Playlist : public Iterable<Song*>{
public: 
    vector<unique_ptr<Song>> songs;

    void addSong(unique_ptr<Song> s) {
        songs.push_back(std::move(s));
    }

    Iterator<Song*>* getIterator() override;
};


class LinkedListIterator : public Iterator<int> {
private:
    LinkedList* curr;
public:
    LinkedListIterator(LinkedList* curr) {
        this->curr = curr;
    }
    bool hasNext() {
        return curr != nullptr;
    }
    int next() {
        int val = curr->data;
        curr = curr->next;
        return val;
    }
};

class PlayListIterator : public Iterator<Song*>{
private:
    const vector<unique_ptr<Song>>& songs;
    size_t index;
public:
    PlayListIterator(const vector<unique_ptr<Song>>& s) : songs(s), index(0) {}
    bool hasNext() override {
        return index < songs.size();
    }
    Song* next() override {
        return songs[index++].get();
    }
};

Iterator<int>* LinkedList::getIterator() {
    return new LinkedListIterator(this);
};

Iterator<Song*>* Playlist::getIterator(){
    return new PlayListIterator(songs);
};


int main(){
    LinkedList* temp = new LinkedList(1);
    temp->next = new LinkedList(2);
    temp->next->next = new LinkedList(3);
    temp->next->next->next = new LinkedList(4);
     
    // Iterator<int>*
    Iterator<int>* it1 = temp->getIterator();

    while(it1->hasNext())    
    cout<<it1->next()<<" ";
    cout<<"\n";

    // Playlist
    Playlist *playlist = new Playlist();
    playlist->addSong( make_unique<Song>("Admirin You", "Karan Aujla"));
    playlist->addSong( make_unique<Song>("Husn", "Anuv Jain"));

    Iterator<Song*>* it2 = playlist->getIterator();
    
    while(it2->hasNext()) {
        Song* s = it2->next();
        cout << s->title << " by " << s->artist << "\n";
    }

    // cleanup
    delete temp->next->next->next;
    delete temp->next->next;
    delete temp->next;
    delete temp;
    delete it1;
    delete playlist;
    delete it2;
    return 0;
}
