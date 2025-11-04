#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
  cout<<"Enter 5 numbers: "<<endl;
  vector<int> My_nums;
  for(int i=0; i<5; i++){
    int num; cin>>num;
    My_nums.push_back(num);
  }

  ofstream fout;
  fout.open("ooutput.txt");

  for(int i=0; i<My_nums.size(); i++){
    fout<<My_nums[i]<<" ";
  }
  fout.close();

  // ofstream outFile("output.txt");
  // for(int i=0; i<My_nums.size(); i++){
  //   outFile<<My_nums[i]<<endl;
  // }
  // outFile.close();
  // return 0;
}