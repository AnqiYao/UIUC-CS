#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int hashFunction(string s, int M) {
   char ch[s.length()];
    for(int i =0 ; i<(int) s.length(); i++)
      ch[i] = s.at(i);
   int sum = 0;
   for( int i =0;i<(int) s.length();i++)
       sum += ch[i];
    return sum%M;
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
 }

int countCollisions (int M, vector<string> inputs) {
	int collisions = 0;
 /*      unordered_map<int,int> hash;
        for(int i = 0;i<(int)inputs.size();i++)
       {   auto lookup = hash.find(hashFunction(inputs[i],M));
           if( lookup != hash.end())
              hash[hashFunction(inputs[i],M)] ++;
           else 
              hash[hashFunction(inputs[i],M)] = 0;
         }     
       for( auto & key : hash)
           collisions += key.second;  */ 
     int arr[M];
     for (int i= 0; i < M;i++)
       arr[i]=-1;
     for ( int i = 0;i<(int)inputs.size();i++)
       {  arr[hashFunction(inputs[i],M)] ++; }
      
     for ( int i = 0; i< M ; i++) 
      {  if( arr[i] >=0 )
         collisions += arr [i] ;
       }
     

 

	return collisions;
}

 int main() {
 	vector<string> inputs {"hi", "i", "richa", "TA", "CS225","fi","hello","weare",
 	"always","there","for","you","valspar","ri","sh","tg","uf","the", "frogurt", "is", 
 	"also", "cursed","Whats", "your", "name", "Homer", "Simpson", "What", "is", "favorite",
 	"team", "The", "Isotopes", "I", "like", "too"};

 	for (int i=1; i<=11; i++) {
 		cout<< "performing hash on the inputs with array size " << to_string(i) << " =>\t"<< to_string(countCollisions(i, inputs)) << endl;
 	}
 	return 1;
 }
