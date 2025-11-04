#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream fin; // Create an input file stream object
    fin.open("example.txt"); // Open the file named "example.txt"
    if(!fin){
        cerr << "Error opening file!" << endl;
        return 1; // Exit if the file cannot be opened
    }

    char ch;
    fin>>ch; // Read a single character from the file
    while(!fin.eof()){
        cout<<ch; // Output the character to the console
        fin>>ch; // Read the next character from the file
    }
    
    cout<<endl; // Print a newline after reading all characters
    // Alternative method to read a character
    fin.clear(); // Clear EOF flag
    fin.seekg(0); // Move the file pointer back to the beginning
    ch = fin.get(); // Read a single character using get()

    while(!fin.eof()){
        cout<<ch; // Output the character to the console
        ch = fin.get(); // Read the next character using get()
    }

    fin.close(); // Close the file
    return 0;
}