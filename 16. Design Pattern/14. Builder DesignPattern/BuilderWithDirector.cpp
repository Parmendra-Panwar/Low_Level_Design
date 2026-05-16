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
    friend class HTTPBuilder;

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

class HTTPBuilder{
    private:
    unique_ptr<HTTP> req;
    public:
    HTTPBuilder() : req(new HTTP()) {}

    HTTPBuilder& withUrl(const string& URL){
        req->url = URL;
        return *this;
    }
    HTTPBuilder& withMethod(const string& method){
        req->method = method;
        return *this;
    }
    HTTPBuilder& withTimeout(const int& time){
        req->timeout = time;
        return *this;
    }

    HTTPBuilder& withHeader(const map<string, string>& Header){
        req->header = Header;
        return *this;
    }

    unique_ptr<HTTP> Build() {
        if (req->url.empty()) throw runtime_error("URL empty");
        return move(req); 
    }
};

class HTTPBuildWithDirector{
    public:
    static unique_ptr<HTTP> GETHTTP(const string url){
        auto req = HTTPBuilder().withUrl(url).withMethod("GET") .Build();
        return req;
    }

    static unique_ptr<HTTP> POSTHTTP(const string url, map<string, string>& header){
        auto req = HTTPBuilder().withUrl(url).withMethod("POST").withHeader(header).Build();
        return req;
    }
};

int main(){
    try {
        auto byBuilderReq = HTTPBuilder().withUrl("example.com").Build();
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