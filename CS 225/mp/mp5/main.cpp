/**
 * @file main.cpp
 * Contains code to test your Quadtree implementation.
 */

#include <iostream>
#include "png.h"
#include "quadtree.h"

using std::cout;
using std::endl;

int main()
{
/*
    PNG imgIn, imgOut;
    imgIn.readFromFile("in.png");

    // test constructor, decompress
    Quadtree halfTree(imgIn, 128);
    imgOut = halfTree.decompress();
    imgOut.writeToFile("outHalf.png");

    // now for the real tests
    Quadtree fullTree;
    fullTree.buildTree(imgIn, 256);

    // you may want to experiment with different commands in this section

    // test pruneSize and idealPrune (slow in valgrind, so you may want to
    // comment these out when doing most of your testing for memory leaks)
    cout << "fullTree.pruneSize(0) = "      << fullTree.pruneSize(0) << endl;
    cout << "fullTree.pruneSize(100) = "    << fullTree.pruneSize(100) << endl;
    cout << "fullTree.pruneSize(1000) = "   << fullTree.pruneSize(1000) << endl;
    cout << "fullTree.pruneSize(100000) = " << fullTree.pruneSize(100000) << endl;

    cout << "fullTree.idealPrune(1000) = "  << fullTree.idealPrune(1000) << endl;
    cout << "fullTree.idealPrune(10000) = " << fullTree.idealPrune(10000) << endl;

    // Test some creation/deletion functions
    Quadtree fullTree2;
    fullTree2 = fullTree;
    imgOut = fullTree2.decompress();
    imgOut.writeToFile("outCopy.png");

    // test clockwiseRotate
    fullTree.clockwiseRotate();
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outRotated.png");

    // test prune
    fullTree = fullTree2;
    fullTree.prune(1000);
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outPruned.png");

    // test several functions in succession
    Quadtree fullTree3(fullTree2);
    fullTree3.clockwiseRotate();
    fullTree3.prune(10000);
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    imgOut = fullTree3.decompress();
    imgOut.writeToFile("outEtc.png");

    // ensure that printTree still works
    Quadtree tinyTree(imgIn, 32);
    cout << "Printing tinyTree:\n";
    tinyTree.prune(100);
    tinyTree.printTree();
*/ 
   PNG imgIn, imgOut, imgOut2;
   imgIn.readFromFile("in.png");
   //imgIn.writeToFile("in_out.png");
   //imgIn.writeToFile("in_out.png");
   // test constructor, decompress
   cout<<"!"<<endl;
   //Quadtree halfTree(imgIn, 0);
   cout<<"2"<<endl;

   //imgOut = halfTree.decompress();
   //cout<<"!"<<endl;
   //imgOut.writeToFile("outHalf.png");

   // now for the real tests
   Quadtree fullTree;
    cout<<"11"<<endl;
   fullTree.buildTree(imgIn, 256);
    cout<<"12"<<endl;
   //fullTree = halfTree;
   // you may want to experiment with different commands in this section
	//fullTree.prune(1000);
   imgOut2 = fullTree.decompress();
     cout<<"22"<<endl;
   imgOut2.writeToFile("full.png");
  //   fullTree.prune(20000);
     //cout<<"out"<<endl;
  //   imgOut = fullTree.decompress();
  //  cout<<"decompree"<<endl;		
   //Quadtree halfTree(fullTree);
   // cout<<halfTree.pruneSize(100)<<endl;
   //imgOut = halfTree.decompress();
 //  imgOut.writeToFile("outHalf.png");
    //   cout<<"main"<<endl;
   // test pruneSize and idealPrune (slow in valgrind, so you may want to
   // comment these out when doing most of your testing for memory leaks)
   cout << "fullTree.pruneSize(0) = " << fullTree.pruneSize(0) << endl;
   cout << "fullTree.pruneSize(100) = " << fullTree.pruneSize(100) << endl;
   cout << "fullTree.pruneSize(1000) = " << fullTree.pruneSize(1000) << endl;
   cout << "fullTree.pruneSize(100000) = " << fullTree.pruneSize(100000) << endl;
   cout<< "idealPrune(1) = " << fullTree.idealPrune(1)<<endl;
   cout << "fullTree.idealPrune(1000) = "  << fullTree.idealPrune(1000) << endl;
   cout << "fullTree.idealPrune(10000) = " << fullTree.idealPrune(10000) << endl;
     cout << "fullTree.idealPrune(18283) = " << fullTree.idealPrune(18283) << endl;
       cout << "fullTree.idealPrune(39256) = " << fullTree.idealPrune(39256) << endl;
      cout << "fullTree.idealPrune(65494) = " << fullTree.idealPrune(65494) << endl;
        cout << "fullTree.idealPrune(65493) = " << fullTree.idealPrune(65493) << endl;
         //cout<<"idealPrune(2) = "<<fullTree.idealPrune(2)<<endl;
 
         cout<<"pruneSize(89646) = " << fullTree.pruneSize(89646)<<endl;   
/*
   // Test some creation/deletion functions
   Quadtree fullTree2;
   fullTree2 = fullTree;
   imgOut = fullTree2.decompress();
   imgOut.writeToFile("outCopy.png");


   // test clockwiseRotate
   halfTree.clockwiseRotate();
   imgOut = halfTree.decompress();
   imgOut.writeToFile("outRotated.png");


   // test prune
   fullTree = halfTree;
   fullTree.prune(1000);
   imgOut = fullTree.decompress();
   imgOut.writeToFile("outPruned.png");
*/
    return 0;
}
