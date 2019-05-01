#include <string>
#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

class HashTable
{
	private:
		vector<string>* table;		// The hash table
		int M;

		unsigned long bernstein(string str, int M)
		{
			unsigned long b_hash = 5381;
			for (int i = 0; i < (int)str.length(); ++i)
			{
				b_hash = b_hash * 33 + str[i];
			}
			return b_hash % M;
		};

	public:
		HashTable(int M)	// M is the size of the hash table
		{
			table = new vector<string>[M];
			this->M = M;
		};					
			
		void printKeys()	// Function to print all keys in the hash table
		{
			for(int i = 0; i < M; ++i)
		             for (auto it = table[i].begin(); it!= table[i].end(); ++it)
					cout<<*it<<"\n";
		};		

		void insert(string str)		//Inserts str into the hash table; must handle duplicates!
		{   
                    
                     bool temp = contains(str);
                         if (temp)
                           return;
                       else{
                         unsigned long a = bernstein(str,M);
                           if(table->size()<M)
                           for(int i = 0; i<M; i++)
                             table->push_back("");
                           table->at(a) = str;
                          
                          }
		};

		bool contains(string str)	//Checks if the hash table contains str
		{   
                      for (std::vector<string>::iterator it = table->begin() ; it != table->end(); ++it) 
                             if( *it == str) 
                                 return true;
                      return false;       
		};
};

int main()
{
	HashTable h(10);
        
	h.insert("aaa"); 
        
	h.insert("aaa");
        
	h.insert("ccc");
	
        cout<<"Does the hash table contain bbb? "<<h.contains("bbb")<<"\n";
	cout<<"Does the hash table contain aaa? "<<h.contains("aaa")<<"\n";
	cout<<"Contents of the hash table:\n";	
	h.printKeys();
}
