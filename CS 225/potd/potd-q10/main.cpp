#include <iostream>
#include <cmath>
#include <array>
using namespace std;

//
// Write the function `raise` that accepts an array of integers and
// an integer as the input parameters.
//
int* raise(int array[], int size)
{ int *arr = new int[size];
  for(int i=0;i<size-2;i++)
    { arr[i]= pow(array[i],array[i+1]);}
  for(int i=size-2;i<size;i++)
     { arr[i]= array[i];}
  for(int i=0;i<size;i++)
     { array[i]= arr[i];}
  for(int i=0;i<size;i++)
      { arr[i]=0;}
   delete[] arr;
   return array;
}

int main() {
  int arr_in[5] = { 1, 2, 3, 4, -1 };
  int *arr_out = raise(arr_in, 5);
  for ( int i = 0;i<5;i++)
     cout<< arr_out[i]<<endl;
  return 0;
}
