#include <iostream>
#include <map>
using namespace std;

long fibonacci(int n) {
  static map<long,long double> map1 = { {1,1.0} , {2,1.0} ,};
  auto lookup = map1.find(n);
  if(lookup != map1.end())
     return lookup->second;
  else 
    {  long result = fibonacci(n-1) + fibonacci(n-2);
       map1[n] = result;
       return result;
    } 
}

 int main() {
   for( int i = 1; i< 1000; i++)
     cout<<"fibonacci("<<i<<") = "<< fibonacci(i)<<endl;
   cout<<"fibonacci(1000) = "<<fibonacci(1000)<<endl;
   cout<<"fibonacci(10000) = "<<fibonacci(10000)<<endl;
   return 0;
 }
