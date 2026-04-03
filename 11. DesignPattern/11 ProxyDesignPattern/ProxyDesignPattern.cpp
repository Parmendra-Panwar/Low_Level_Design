#include <iostream>
#include <memory>
using namespace std;

class IDataLoader{
    public:
    virtual ~IDataLoader() {};
    virtual void fetchData()=0;
};

class DataLoader : public IDataLoader{
    public:
    void fetchData() override {
        cout<<"fetchData Is Called\n";
    }
};

class DataLoaderProxy : public IDataLoader{
    unique_ptr<DataLoader> dl;
    public:
    DataLoaderProxy(){
        dl = nullptr;
        cout<<"data loader proxy created\n";
    }
    void fetchData() override {
        if(dl == nullptr) dl = make_unique<DataLoader>();
        dl->fetchData();
    }
};

int main(){
    unique_ptr<IDataLoader> dlp = make_unique<DataLoaderProxy>();
    dlp->fetchData();
}


















// class IDataLoader{
//     public:
//     virtual ~IDataLoader() {};
//     virtual void fetchData()=0;
// };

// class DataLoader : public IDataLoader{
//     public:
//     void fetchData() override {
//         cout<<"fetchData Is Called";
//     }
// };

// class DataLoaderProxy : public IDataLoader{
//     DataLoader* dl;
//     public:
//     DataLoaderProxy(){
//         dl = nullptr;
//         cout<<"data loader proxy created";
//     }
//     void fetchData() override {
//         if(dl == nullptr) dl = new DataLoader;
//         dl->fetchData();
//     }

//     ~DataLoaderProxy(){
//         delete dl;
//     }
// };

// int main(){
//     IDataLoader* dlp = new DataLoaderProxy;
//     dlp->fetchData();
//     delete dlp;
//     return 0;
// }