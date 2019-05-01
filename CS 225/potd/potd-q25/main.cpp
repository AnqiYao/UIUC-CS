#include <iostream>
using namespace std;


int main(int argc, char** argv) {
  if (argc >= 1) {
    string s(argv[1]);   
    // Your code here
   if(s.length()<2)
   cout<< "Good Luck!" <<endl;
   else if(s.length()<4)
   cout<< "Happy 2017!"<<endl;
   else if(s.length()<6)
   cout<<"Make American Great Again!"<<endl;
   else if(s.length()<8)
   cout<<"May you find what you are looking for"<<endl;
   else if(s.length()>7)
   cout<<"It's what you choose define who you are."<<endl;
    return 0;
  } else {
    cout<<"Usage: "<<argv[0]<<" <word>"<<endl;
    return 1;
  }
}
