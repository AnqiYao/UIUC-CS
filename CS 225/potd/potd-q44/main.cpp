#include <iostream>
#include <vector>
#include <map>

using namespace std;


vector<int> orderedGroup(int arr[], int size) {
     vector <int> vec1;
      for(int i = 0;i< sizeof(arr);i++)
   {     for (int j = 0; j< i ; j++)
       {      if (arr[j]>arr[i]){
                 int temp = arr[i];
                 arr [i] = arr [j];
                 arr [j] = temp;
            }
        }
    }       
     for( int i =0; i < sizeof(arr); i++)
         vec1.push_back(arr[i]);
    return vec1;
}

void printVector(vector<int> vec) {
    cout << "Output: <";
    for (size_t i = 0; i < vec.size(); i++)
        cout << "  " << vec[i];
    cout << " >" << endl;
}

int main() {
    // Test1
    int arr1[] = {1, 2, 2, 3, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printVector(orderedGroup(arr1, n1)); // Output: <1, 2, 2, 2, 3, 3, 4 >

    // Test2
    int arr2[] = {1, 2, 3, 2, 5, 6, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printVector(orderedGroup(arr2, n2)); // Output: <1, 2, 2, 3, 5, 5, 6 >

    // Test3
    int arr3[] = {2, 4, 1, 3, 3, 2, 4, 1, 1, 2, 4, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printVector(orderedGroup(arr3, n3)); // Output: <2, 2, 2, 4, 4, 4, 1, 1, 1, 3, 3, 3 >

    return 0;
}
