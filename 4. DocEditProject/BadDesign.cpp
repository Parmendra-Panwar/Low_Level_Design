#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DocumentEditor{
  private: 
    vector <string> DocumentElem;
    string RenderDocument;

  public:
    // push the text and image to dataset
    void AddText(string text){
      DocumentElem.push_back(text);
    }
    void AddImage(string imagePath){
      DocumentElem.push_back(imagePath);
    }
    // render the document
    string renderDocument(){
      if(RenderDocument.empty()){
        string res;
        for(auto elem: DocumentElem){
          if(elem.size() > 4 && elem.substr(elem.size() - 4) == ".png"){
            res += "<image src='" + elem + "' />\n";
          } else {
            res += "<p>" + elem + "</p>\n";
          }
        }
        RenderDocument = res;
      }
      return RenderDocument;
    }

    void SaveToFile(){
      ofstream outFile("doucment.txt");
      if(outFile.is_open()){
        outFile << renderDocument();
        outFile.close();
        cout << "Document saved successfully." << endl;
      }else{
        cout << "Error opening file for writing." << endl;
      }
    }
};

int main(){
  DocumentEditor editor;
  editor.AddImage("image1.png");
  editor.AddText("This is a sample text.");
  editor.AddImage("image2.png");
  editor.AddText("Another piece of text.");

  cout << editor.renderDocument() << endl;

  editor.SaveToFile();
  return 0;
}