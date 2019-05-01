#include <iostream>
#include <queue>
#include <string>
using namespace std;

vector<int> checkSums(vector<int> v){

  vector<int> sum; 
  vector<int> temp;
  temp = v;
  for(int i = 0; i< v.size(); i++){
   for( int k = 0; k< i ; k++){
       if(temp[i]<temp[k]) 
       {  int temp1 = temp[i];
          temp[i] = temp[k];
          temp[k] = temp1;
       }
     }
  }
  int first = temp[0] + temp [1];
  int second = temp[temp.size()-1]+temp[temp.size()-2];
  sum.push_back(second);
  sum.push_back(first);
	//write your code here

	return sum;
}


int main(){

vector<int> v1;

v1 = {20,32,12,65,0,19,76,15,2,39};

vector<int>answer = checkSums(v1);

cout << "The sum of the sum of the largest two elements is " << answer[0] <<endl;
cout << "The sum of the sum of the smallest two elements is " << answer[1] <<endl;

return 0;

}
