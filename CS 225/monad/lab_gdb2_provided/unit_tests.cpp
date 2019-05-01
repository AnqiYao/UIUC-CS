#include <cmath>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include "proxy.h"
#include "skipList.h"

using namespace std;

/**
  *
  * Tests written by Jordi Paris Ferrer
  * For CS225 - Fall 2016
  *
  */

int probability = 50;
int maxLevel = 50;

void assertEqual(vector<int> a, vector<int> b, bool rev = false)
{
    if(a.size() != b.size())
        FAIL("List sizes don't match");

    for(int i = 0; i < a.size(); i++)
       if(a[i] != b[i])
          FAIL (rev ? "List keys don't match" : "List keys don't match when traversed in reverse") ;
}

void removeSentinels(vector<int> & a)
{
    a.erase(a.begin());
    a.pop_back();
}

UNIT_TEST(testFind1, 5, 5, 1000)
{
    // search has random elements
    srand(time(NULL));

    cout << time(NULL) << endl;

    SkipList list(probability, maxLevel);
    int key = 7;

    RGBAPixel c(137, 137, 137);
    list.insert(key, c);

    RGBAPixel ret = list.search(7);

    if(ret != c)
    {
        stringstream s;
        s << "ret != solution: " << ret << " != " << c;
        FAIL(s.str());
    }
}


UNIT_TEST(testFind2, 5, 5, 1000)
{
    SkipList list(probability, maxLevel);
    int key = 7;

    RGBAPixel c(137, 137, 137);
    list.insert(key, c);

    RGBAPixel ret = list.search(5);

    if(ret != RGBAPixel(0, 0, 0, 50))
    {
        stringstream s;
        s << "ret != solution: " << ret << " != " << RGBAPixel(0, 0, 0, 50);
        FAIL(s.str());
    }
}

UNIT_TEST(testFind3, 10, 10, 1000)
{
    SkipList list(probability, maxLevel);

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 100; i += 2)
    {
        if(i == 7)
            list.insert(i, RGBAPixel(42, 42, 42));
        else
            list.insert(i, c);
    }

    RGBAPixel ret = list.search(7);

    if(ret != RGBAPixel(42, 42, 42))
    {
        stringstream s;
        s << "ret != solution: " << ret << " != " << RGBAPixel(42, 42, 42);
        FAIL(s.str());
    }
}

UNIT_TEST(testInsertAscending, 5, 5, 1000)
{
    SkipList list(probability, maxLevel);
    vector<int> soln;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        list.insert(i, c); 

        soln.push_back(i);
    }

    // get the traverse map
    vector<int> check = list.traverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);
}


UNIT_TEST(testInsertAscendingBack, 5, 5, 1000)
{
    SkipList list(probability, maxLevel);
    vector<int> soln;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        list.insert(i, c); 

        soln.push_back(i);
    }

    // get the reversed traverse map
    vector<int> check = list.traverseReverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln, true);
}


UNIT_TEST(testInsertRandom, 10, 10, 2000)
{
    SkipList list(probability, maxLevel);
    vector<int> soln;
    vector<int> keys;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        keys.push_back(i);
        soln.push_back(i);
    }

    random_shuffle(keys.begin(), keys.end()); 

    for(int k : keys)
        list.insert(k, c);

    // get the traverse map
    vector<int> check = list.traverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);

}


UNIT_TEST(testInsertRandomBack, 10, 10, 2000)
{
    SkipList list(probability, maxLevel);
    vector<int> soln;
    vector<int> keys;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        keys.push_back(i);
        soln.push_back(i);
    }

    random_shuffle(keys.begin(), keys.end()); 

    for(int k : keys)
        list.insert(k, c);

    // get the backwards traverse map
    vector<int> check = list.traverseReverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln, true);
}


UNIT_TEST(testRemoveEasy, 5, 5, 1000)
{
    SkipList list(probability, maxLevel);

    vector<int> soln;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i <= 10; i++)
    {
        if(i != 7)
        {
            list.insert(i, c);
            if(i != 3)
                soln.push_back(i);
        }
    }

    bool ret1 = list.remove(3);
    bool ret2 = list.remove(7);

    list.printKeys();
    list.printKeysReverse();

    if(ret1 == false || ret2 == true)
        FAIL("Incorrect return value");

    // get traverse map
    vector<int> check = list.traverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);

    check = list.traverseReverse();
    removeSentinels(check);
    assertEqual(check, soln, true);
}



VALGRIND_TEST(testConstructor1, 10, 10, 1000)
{
    SkipList list (1337, RGBAPixel(137, 137, 137));

    vector<int> soln;

    soln.push_back(1337);

    list.printKeys();
    list.printKeysReverse();

    vector<int> check = list.traverse();
    removeSentinels(check);
    assertEqual(check, soln);

    check = list.traverseReverse();
    removeSentinels(check);

    assertEqual(check, soln, true);
}

VALGRIND_TEST(testConstructor2, 10, 10, 1000)
{
    SkipList list (1337, RGBAPixel(137, 137, 137));
    list.insert(42, RGBAPixel(42, 42, 42));
    list.insert(9999, RGBAPixel(99, 99, 99));

    vector<int> soln;

    soln.push_back(42);
    soln.push_back(1337);
    soln.push_back(9999);


    list.printKeys();
    list.printKeysReverse();

    vector<int> check = list.traverse();
    removeSentinels(check);
    assertEqual(check, soln);

    check = list.traverseReverse();
    removeSentinels(check);

    assertEqual(check, soln, true);
}
