// Your code here
#include <iostream>
#include <string>

using namespace std;

class food {
public:

food();
food(string name,int quantity);
void setName(string a);
void setQuantity(int q);
string getName();
int getQuantity();



private:
string name; 
int quantity;


};
