#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

vector<string> getString(string pattern){
     vector<string> a;
    while(pattern.find(" ")!=std::string::npos){
        string temp = pattern.substr(0,pattern.find(" "));
        a.push_back(temp);
        pattern = pattern.substr(pattern.find(" ")+1);
     }
     a.push_back(pattern);
     return a;
 }

bool wordPattern(string pattern, string str) {
    map<char,string> table;
    vector<string> a = getString(str);
    for( size_t i  = 0; i< a.size(); i++)
        cout<<a[i]<<endl;
    if(a.size()!=pattern.length())
        return false;
  else {
    for(size_t i = 0; i<pattern.length();i++){
    auto lookup = table.find(pattern[i]);
    if(lookup == table.end())
       table[pattern[i]] = a[i];
    else {
       if(table[pattern[i]]!=a[i])
           return false;
       }
     }
      return true;
    }
      
     


    //write your code here
}

int main(){

string s1= "dog cat cat cat cat cat cat cat dog";
string p1 = "abbbbbbba";
string s2 = "fish dog dog dog dog dog dog cat";
string p2 = "abbbbbba";

cout << " The pattern p1 matches string s1 " << wordPattern(p1,s1)<< endl;
cout << " The pattern p2 matches string s2 " << wordPattern(p2,s2)<< endl;
 





return 0;

}


