#include <string>
#include <iostream>
#include<algorithm>
using namespace std;

unsigned long bernstein(string str, int M)
{
	unsigned long b_hash = 5381;
        for ( size_t  i = 0; i< str.length();i++)
        b_hash =  b_hash * 33 + str[i];
        //Your code here
	return b_hash % M;
}

string reverse(string str)
{
	string output = "";
        for(int i = str.length()-1; i>=0;i--)
           output += str[i];
	//Your code here

	return output;
}

int main()
{
	string s = "POTS";
        cout<<reverse(s)<<endl;
	int M = 13;
	cout<<"Bernstein hash of "<<s<<" with range "<<M<<" is: "<<bernstein(s, M)<<'\n'; 	
	cout<<"Bernstein hash of the reverse of "<<s<<" - " <<reverse(s)<<" - with range "<<M<<", is: "<<bernstein(reverse(s), M)<<'\n';
}
