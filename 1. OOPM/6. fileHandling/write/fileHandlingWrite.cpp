#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream outFile; // Create an output file stream object
    outFile.open("example.txt"); // Open a file named "example.txt" for writing
    outFile << "Hello, World!" << endl; // Write a line to the file
    outFile.close(); // Close the file
    return 0;
}