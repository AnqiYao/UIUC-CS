#include <iostream>
#include <cstring>
#include <cstddef>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

bool isSame(string temp1, string temp2){
  if(temp1.size()!=temp2.size())
      return false;  
  map<char,char> map1;
  vector<char> store;
  for(int i = 0; i<temp2.size();i++){
     auto lookup = map1.find(temp1[i]);
     if(lookup == map1.end()){
        for(size_t k = 0; k < store.size(); k++){
            if (store[k] == temp2[i])
             return false;
           }           
        map1[temp1[i]]= temp2[i];
        store.push_back(temp2[i]);
     }
    else {
       if(lookup->second != temp2[i])
         return false;
       }   
    }
     return true;
}  

int main(){

cout<<isSame("egg", "add")<<endl;

cout<<isSame("foo","bar")<<endl;

cout<<isSame("paper", "title")<<endl;

cout<<isSame("move", "hood")<<endl;

cout<<isSame("boo", "boo")<<endl;


return 0; 
 
}



