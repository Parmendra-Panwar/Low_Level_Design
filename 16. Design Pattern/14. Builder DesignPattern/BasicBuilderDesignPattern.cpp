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

    HTTPBuilder& withHeader(const map<string, string>& Header){
        req->header = Header;
        return *this;
    }

    unique_ptr<HTTP> Build() {
        if (req->url.empty()) throw runtime_error("URL empty");
        return move(req); 
    }
};


int main(){
    try {
        auto req = HTTPBuilder().withUrl("example.com").Build();
        req->execute();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}