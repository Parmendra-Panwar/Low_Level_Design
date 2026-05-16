#include <iostream>
#include <map>
#include <memory>
using namespace std;

class HTTP{
    private:
    string url = "";
    string method;
    int timeout = 30;
    map<string, string> header;

    HTTP(){}
    public:
    friend class StepBuilder;

    void execute() {
        cout << "Executing " << method << " request to " << url << endl;
        cout << "Headers:" << endl;
        for (const auto& h : header) {
            cout << "  " << h.first << ": " << h.second << endl;
        }
        
        cout << "Timeout: " << timeout << " seconds" << endl;
        cout << "Request executed successfully!" << endl;
    }
};


class MethodStep;
class TimeoutStep;
class OptionalStep;

class URLStep{
    public:
    virtual MethodStep& withURL(const string& url) = 0;
};
class MethodStep{
    public:
    virtual TimeoutStep& withMethod(const string& method) = 0;
};
class TimeoutStep{
    public:
    virtual OptionalStep& withTimeout(const int& time) = 0;
};
class OptionalStep{
    public:
    virtual ~OptionalStep() {}
    virtual OptionalStep& withHeader(const map<string, string>& mp) = 0;
    virtual unique_ptr<HTTP> build() = 0;
};

class StepBuilder :
    public URLStep,
    public MethodStep,
    public TimeoutStep,
    public OptionalStep
{
    private:
    unique_ptr<HTTP> req;
    public:
    StepBuilder() : req(new HTTP()) {}

    StepBuilder& withURL(const string& URL) override {
        req->url = URL;
        return *this;
    }
    StepBuilder& withMethod(const string& method) override {
        req->method = method;
        return *this;
    }
    StepBuilder& withTimeout(const int& time) override{
        req->timeout = time;
        return *this;
    }

    StepBuilder& withHeader(const map<string, string>& Header) override {
        req->header = Header;
        return *this;
    }

    unique_ptr<HTTP> build() override {
        if (req->url.empty()) throw runtime_error("URL empty");
        return move(req); 
    }
    
    static unique_ptr<StepBuilder> getBuilder() {
        return make_unique<StepBuilder>();
    }
};

class HTTPBuildWithDirector{
    public:
    static unique_ptr<HTTP> GETHTTP(const string url){
        auto req = StepBuilder::getBuilder()->withURL(url).withMethod("GET").withTimeout(30).build();

        return req;
    }

    static unique_ptr<HTTP> POSTHTTP(const string url, map<string, string>& header){
        return StepBuilder::getBuilder()->withURL(url).withMethod("POST").withTimeout(30).withHeader(header).build();
    }
};

int main(){
    try {
        auto byBuilderReq = StepBuilder::getBuilder()->withURL("Semple.com").withMethod("PUT").withTimeout(25).build();
        byBuilderReq->execute();

        auto getReqByDirector = HTTPBuildWithDirector::GETHTTP("Test.com");
        getReqByDirector->execute();

        map<string, string> temp;
        temp["test header"] = "Check Done";
        auto postReqByDirector = HTTPBuildWithDirector::POSTHTTP("Test.com", temp);
        postReqByDirector->execute();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}