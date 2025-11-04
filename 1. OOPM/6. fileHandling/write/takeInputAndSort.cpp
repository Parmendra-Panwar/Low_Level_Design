#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){
    cout<<"Enter the number of elems"<<endl;
    int n;
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter the elements"<<endl;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    // writing to file
    ofstream fout("data.txt");
    fout<<"Unsorted elements are: "<<endl;
    for(int i=0; i<n; i++){
        fout<<arr[i]<<" ";
    }
    fout<<endl;
    // sorting
    sort(arr.begin(), arr.end());
    fout<<"Sorted elements are: "<<endl;
    for(int i=0; i<n; i++){
        fout<<arr[i]<<" ";
    }

    fout.close();
    return 0;
}