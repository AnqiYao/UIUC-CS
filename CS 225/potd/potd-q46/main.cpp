#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

unsigned long bernstein(string str, int M)
{
	unsigned long b_hash = 5381;
	for (int i = 0; i < (int) str.length(); ++i)
	{
		b_hash = b_hash * 33 + str[i];
	}
	return b_hash % M;
}

float hash_goodness(string str, int M)
{
	vector<string> array[M];	// Hint: This comes in handy
//	vector<string>* array = new vector<string>[M];	// Hint: This comes in handy
        
 	int permutation_count = 0;	
	float goodness = 0;
	do {   
		if (permutation_count == M) break;
                  
	      	// Code for computing the hash and updating the array
	} while(std::next_permutation(str.begin(), str.end()));
         	
	//Code for detecting number of collisions
	return goodness;
}

int main()
{
	string s = "arbitrary";
	for (int i = 51; i <= 100; ++i)
	{	
		cout<<"Goodness of hash Bernstein hash function for "<<s<<" with range="<<i<<" is: "<<hash_goodness(s,i)<<"\n";	
	}	

}
