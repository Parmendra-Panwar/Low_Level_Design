#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Base class for document elements
class DocumentElement{
  public:
    virtual string render() = 0;
};
class TextElement : public DocumentElement{
  private:
    string text;
  public: 
    TextElement(string t){
      this->text = t;
    }
    string render() override{
      return "<p>" + text + "</p>\n";
    }
};
class ImageElement : public DocumentElement{
  private:
    string imagePath;
  public:
    ImageElement(string imagePath){
      this->imagePath = imagePath;
    }
    string render() override{
      return "<img src='" + imagePath + "' />\n";
    }
};
class NewLineElement : public DocumentElement{
  public:
    string render() override{
      return "\n";
    }
};
class TabSpaceElement : public DocumentElement{
  public:
    string render(){
      return "\t";
    }
};

// Document class to manage document elements
class Document{
  private:
    vector <DocumentElement*> elements;

  public:
    void AddElement(DocumentElement* elem){
      elements.push_back(elem);
    }
    
    string render(){
      // Render Logic
      string res;
      for(auto elem: elements){
        // Determine type and render accordingly
        res += elem->render();
      }
      return res;
    }
};

// Persistence interface and implementations
class Persistence {
  public:
    virtual void save(string data) = 0;
};
class saveToFile : public Persistence {
  public:
    void save(string data) override{
      ofstream outFile("goodDesign_document.txt");
      if(outFile){
        outFile << data;
        outFile.close();
        cout << "Document saved successfully." << endl;
      }else{
        cout << "Error opening file for writing." << endl;
      }
    }
};
class saveToDatabase : public Persistence{
  public:
    void save(string data) override{
      // Simulate saving to database
      cout << "Document saved to database: " << data << endl;
    }
};


class DocumentEditor{
  private: 
    Document *document;
    Persistence *persistence; // save to file is the persistence here
    string RenderedDocument;

  public:
    DocumentEditor(Document* document, Persistence* persistence){
      this->document = document;
      this->persistence = persistence;
    }

    void AddText(string text){
      document->AddElement(new TextElement(text));
    }
    void AddImage(string imagePath){
      document->AddElement(new ImageElement(imagePath));
    }
    void AddNewLine(){
      document->AddElement(new NewLineElement());
    }
    void AddTabSpace(){
      document->AddElement(new TabSpaceElement());
    }
    string renderDocument(){
      if(RenderedDocument.empty()){
        RenderedDocument = document->render();
      }
      return RenderedDocument;
    }
    void SaveDocument(){
      persistence->save(renderDocument());
    }
};

int main(){
  Document* document = new Document();
  Persistence* persistence = new saveToFile();

  DocumentEditor* Documenteditor = new DocumentEditor(document, persistence);
  Documenteditor->AddImage("image1.png");
  Documenteditor->AddText("This is a sample text.");
  Documenteditor->AddNewLine();
  Documenteditor->AddImage("image2.png");
  Documenteditor->AddTabSpace();
  Documenteditor->AddText("Another piece of text.");
  // Render and save
  cout << Documenteditor->renderDocument() << endl;
  Documenteditor->SaveDocument();

  return 0;
}