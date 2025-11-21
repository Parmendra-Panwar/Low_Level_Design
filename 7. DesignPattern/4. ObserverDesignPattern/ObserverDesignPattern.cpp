#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class ISubscriber
{
    public:
    virtual void update() = 0;
    virtual ~ISubscriber() {};
};

class IChannel
{
    public:
    virtual void subscribe(ISubscriber *subs) = 0;
    virtual void unsubscribe(ISubscriber *subs) = 0;
    virtual void notify() = 0;
    virtual ~IChannel() {}
};

class Channel : public IChannel
{
private:
    string name;
    vector<ISubscriber *> Subscribers;
    string latestVideo;

public:
    Channel(const string &name)
    {
        this->name = name;
    }

    void subscribe(ISubscriber *subs) override
    {
        if (find(Subscribers.begin(), Subscribers.end(), subs) == Subscribers.end())
        {
            Subscribers.push_back(subs);
        }
    }

    void unsubscribe(ISubscriber *subs) override
    {
        auto it = find(Subscribers.begin(), Subscribers.end(), subs);
        if (it != Subscribers.end())
        {
            Subscribers.erase(it);
        }
    }

    void uploadVideo(const string &title)
    {
        latestVideo = title;
        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
        notify();
    }
    void notify() override
    {
        for (ISubscriber *sub : Subscribers)
        {
            sub->update();
        }
    }
    string getVideoData() {
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }
};

class Subscriber : public ISubscriber
{
private:
    string name;
    Channel *channel;

public:
    Subscriber(string name, Channel *channel)
    {
        this->name = name;
        this->channel = channel;
    }
    void update() override {
        cout << "Hey " << name << "," << this->channel->getVideoData();
    }
};

int main()
{
    Channel *chen = new Channel("coder army");
    Subscriber *subs1 = new Subscriber("Rahul", chen);
    Subscriber *subs2 = new Subscriber("Sayam", chen);

    chen->subscribe(subs1);
    chen->subscribe(subs2);

    chen->uploadVideo("Observer Pattern Tutorial");

    chen->unsubscribe(subs1);

    chen->uploadVideo("Decorator Pattern Tutorial");
    delete subs1;
    delete subs2;
    delete chen;
    return 0;
} 