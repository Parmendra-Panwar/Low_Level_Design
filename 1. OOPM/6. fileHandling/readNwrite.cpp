#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ofstream fout("getLine.txt");
    fout<<"Hello World"<<endl;
    fout<<"hello paras"<<endl;
    fout<<"Hello everyone"<<endl;
    fout.close();

    ifstream fin("getLine.txt");
    string str;

    while(getline(fin, str)){
        cout<<str<<endl;
    }
    fin.close();
    return 0;
}