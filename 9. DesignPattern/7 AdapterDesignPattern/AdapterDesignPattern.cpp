#include <iostream>
using namespace std;

// 1. Target interface JO client access karega
class IReport {
public:
    // here takes the row fata string and return Json
    virtual string getJsonData(const string& data) = 0;
    virtual ~IReport(){};
};

// 2. the adaptee: provide XML data from a raw input 
class XmlDataProvider {
public:
    string getXmlData(const string& data){
        size_t sep = data.find(':');
        string name = data.substr(0, sep);
        string id = data.substr(sep+1);

        return "<user>"
                "<name>" + name + "</name>"
                "<id>" + id + "</id>"
                "</user>";
    }
};

// 3. Adapter: convert XML to JSON
class XmlDataProviderAdapter : public IReport{
private:
    XmlDataProvider* xmlProvider;
public:
    XmlDataProviderAdapter(XmlDataProvider* provider){
        this->xmlProvider = provider;
    }

    string getJsonData(const string& data) override {
        // 1. Get XML data fron raw data 
        string xml = xmlProvider->getXmlData(data);

        // 2. converting XML to JSON
        size_t startName = xml.find("<name>")+6;
        size_t endName   = xml.find("</name>");
        string name      = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>")+4;
        size_t endId   = xml.find("</id>");
        string id      = xml.substr(startId, endId-startId); 

        return "{\"name\":\"" + name + "\", \"id\":" + id +  "}";
    }
};

// 4. client class
class Client {
public: 
    // client bas bolta hai mujhe JSON data dedo
    void getReport(IReport* report, string rawData){
        cout << "Processed JSON " 
        << report->getJsonData(rawData) << endl;
    }
};

int main(){
    // 1. create a adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider();
    
    // 2. Make our adapter jo adaptee ko adapt karega
    IReport* adapter = new XmlDataProviderAdapter(xmlProv);

    // 3. Give it some rowdata
    string rawData = "Alice:42";

    // 4. client prints the Json
    Client* client = new Client();
    client->getReport(adapter, rawData);

    // 5. cleanUp
    delete adapter;
    delete xmlProv;
    return 0;
}