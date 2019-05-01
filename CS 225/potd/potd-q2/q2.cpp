/* Problem of the Day #2 */

#include <ctime>
#include <iostream>

using namespace std;

int main() {
  time_t sec_since_epoch = time(nullptr);
  cout<<"Hours: "<<sec_since_epoch/3600<<endl;
  cout<<"Days: "<<sec_since_epoch/86400<<endl;
  cout<<"years: "<<sec_since_epoch/31536000<<endl;


  return 0;
}
