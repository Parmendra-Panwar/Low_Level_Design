#include <vector>
#include <iostream>
#include <string>

using namespace std;

class FileSystemItem {
    public:
    virtual ~FileSystemItem(){};
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual string getName() = 0;
    virtual FileSystemItem* cwd(const string& s) = 0;
    virtual int getSize() = 0;
    virtual bool isFolder() = 0;
};

class File : public FileSystemItem {
    private:
        string name;
        int size;
    public:
        File(string s, int n){
            name = s;
            size = n;
        }

        void ls(int indent) override { 
            cout << string(indent, ' ') << name << endl;
        }

        void openAll(int indent = 0) override {
            cout << string(indent, ' ') << name <<endl;
        }

        string getName() override {
            return name;
        }

        int getSize() override {
            return size;
        };

        bool isFolder() override {
            return false;
        }

        FileSystemItem* cwd(const string& s) override {
            return nullptr;
        }
};

class Folder : public FileSystemItem {
    private:
        string name;
        int size;
        vector<FileSystemItem*> nestedItems;

    public:
        Folder(string s){
            name = s;
            size = 0;
        }

        string getName() override {
            return name;
        }

        int getSize() override {
            if(size != 0) return size;

            for(FileSystemItem* item : nestedItems)
            size += item->getSize();
            
            return size;
        }

        bool isFolder() override {
            return true;
        }

        void addFile(File* fs){
            nestedItems.push_back(fs);
        }

        void addFolder(Folder* fd){
            nestedItems.push_back(fd);
        }

        void ls(int indent = 0) override {
            for(FileSystemItem* item : nestedItems)
            if(item->isFolder()) cout<< " + " << item->getName() << endl;
            else cout<< "   " << item->getName() << endl;
        }

        void openAll(int indent = 0) override {
            cout << string(indent, ' ') << "+ " << name << "\n";
            for(FileSystemItem* item : nestedItems)
            item->openAll(indent + 4); 
        }

        FileSystemItem* cwd(const string& s) override {
            for(FileSystemItem* item : nestedItems)
            if(item->isFolder() && item->getName() == s){
                return item;
            }
            return nullptr;
        }
};

int main() {
    Folder* root = new Folder("root");

    root->addFile(new File("file1.txt", 1));
    root->addFile(new File("file2.txt", 1));
    root->addFile(new File("file3.txt", 1));
    
    Folder* f1 = new Folder("folder1");
    f1->addFile(new File("file2.txt", 1));
    f1->addFile(new File("file3.txt", 1));

    root->addFolder(f1);
    
    root->openAll();
    delete root;
    
    return 0;
}