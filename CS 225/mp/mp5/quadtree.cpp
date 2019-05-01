/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"
#include <iostream>
using namespace std;
/*default constructor for quadtree
 */
Quadtree::Quadtree(){
     root =NULL;
     sideLen = 0;
}



/*constructor for quadtree
 */ 
Quadtree::Quadtree(PNG const& source, int resolution){
      if(resolution == 0){
        cout<<"!"<<endl;
        root = NULL;
        sideLen = 0;
         }
      else {
        root = helpBuild(source,0,0,resolution);
        sideLen = resolution;
       }
}


 
/*copy constructor
 */
Quadtree::Quadtree(Quadtree const& other){
   root = copy(other.root);
   sideLen = other.sideLen;
}



/*destructor for quadtree
 */
Quadtree::~Quadtree(){
clear();
}



/* operator= overwritting
 */ 
Quadtree const& Quadtree::operator=(Quadtree const &other) {
if(this!=&other){
 clear();
 root = copy(other.root);
}
return *this;
}



/* buildtree function
 */
void Quadtree::buildTree(PNG const& source, int resolution){
          clear();
      if(resolution == 0){
          root = NULL;
          sideLen = 0;
         }
      else 
        {
         sideLen = resolution;
         root = helpBuild(source,0,0,resolution);
         }
}



/* getPixel function
 */
RGBAPixel Quadtree::getPixel(int x,int y) const {
     if( x>=sideLen||y>=sideLen||x<0||y<0||root == NULL){
        RGBAPixel temp;
         return temp; }
     QuadtreeNode* temp = findNode(x,y,sideLen,root);
     return temp->element;
}      



PNG Quadtree::decompress()const{
     if(root == NULL){
       PNG temp; 
       return temp; 
       }
     PNG temp1(sideLen,sideLen);
     for (int i =0; i < sideLen; i++){
        for ( int k =0; k< sideLen; k++){
             *temp1(i,k) = getPixel(i,k);
        }
      }
      return temp1; 
  
}





/* -------------------------------------------
 * divide mp 5.1 and mp 5.2  
 */


void Quadtree::clockwiseRotate(){
     helpRotate(root);   
}

void Quadtree::prune(int tolerance){
     if(root == NULL||tolerance < 0)
		return;	
     cout<<"big"<<endl;
     helpPrune(root,tolerance);
     cout<<"end"<<endl;
}


int Quadtree::pruneSize(int tolerance) const {
      if(root ==NULL||tolerance<0)
         return 0;
      int result = countNum(root,root,tolerance);
       return result;
}	

int Quadtree::idealPrune(int numLeaves) const {
     if(root==NULL)
         return 0;
     if(numLeaves >= pruneSize(0))
          return 0;
     int max = 89646;
     if(pruneSize(max)>1)
           max= max * 2;
     int result = leastT(0,max,numLeaves);  
     
     if( pruneSize(result) <= numLeaves){   
      while( pruneSize(result-1) <= numLeaves && result-1 >=0)
            result = result -1;            
       }
     else if( pruneSize(result)> numLeaves){
        while( pruneSize(result) > numLeaves)
              result = result + 1;
       }
       return result;
}  



















//The functions below are the help functions 


/* help function for destructor
 */
void Quadtree::clear(){
  clearRoot(root);
}


/* recursion help function to help clear
 */
void Quadtree::clearRoot(QuadtreeNode* &subroot){
      if(subroot==NULL)
         return;
      clearRoot(subroot->nwChild);
      clearRoot(subroot->neChild);
      clearRoot(subroot->swChild);
      clearRoot(subroot->seChild);
            delete subroot;
            subroot = NULL;
     }


/*help function copy
 */
Quadtree::QuadtreeNode* Quadtree::copy(const QuadtreeNode* subroot){
   if(subroot == NULL)
        return NULL;
        QuadtreeNode* newroot = new QuadtreeNode();
        newroot->element = subroot->element;
      newroot->nwChild = copy(subroot->nwChild);
      newroot->neChild = copy(subroot->neChild);
      newroot->swChild = copy(subroot->swChild);
      newroot->seChild = copy(subroot->seChild);
            return newroot;
}


/*help function for buildtree and also the constructor
 */
Quadtree::QuadtreeNode* Quadtree::helpBuild(PNG const& source,int startX, int startY, int resolution){
     if(resolution == 1){
        QuadtreeNode* subroot = new QuadtreeNode();
        subroot->nwChild = NULL;
	subroot->neChild = NULL;
	subroot->swChild = NULL;
	subroot->seChild = NULL;
        subroot->element = *source(startX,startY);
        return subroot;
           } 
      QuadtreeNode* subroot = new QuadtreeNode();
      subroot->nwChild = helpBuild(source,startX,startY,resolution/2);
      subroot->neChild = helpBuild(source,startX+resolution/2,startY,resolution/2);
      subroot->swChild = helpBuild(source,startX,startY+resolution/2,resolution/2);  
      subroot->seChild = helpBuild(source,startX+resolution/2,startY+resolution/2,resolution/2);
      
      subroot->element.red = (subroot->nwChild->element.red + subroot->neChild->element.red + subroot->swChild->element.red + subroot->seChild->element.red)/4;
      subroot->element.blue = (subroot->nwChild->element.blue + subroot->neChild->element.blue + subroot->swChild->element.blue + subroot->seChild->element.blue)/4;
      subroot->element.green = (subroot->nwChild->element.green + subroot->neChild->element.green + subroot->swChild->element.green + subroot->seChild->element.green)/4;
      subroot->element.alpha = (subroot->nwChild->element.alpha + subroot->neChild->element.alpha + subroot->swChild->element.alpha + subroot->seChild->element.alpha)/4;   

      return subroot;
}


/* To find the right quadtree node for the getpixel function
 */
Quadtree::QuadtreeNode* Quadtree::findNode(int x, int y,int resolution,QuadtreeNode* subroot) const {
    if(subroot->nwChild == NULL) 
          return subroot;
 else 
  {
   if(x<resolution/2) {
          if ( y< resolution/2) 
                   return findNode(x,y,resolution/2,subroot->nwChild);
          else 
              return findNode(x,y-resolution/2,resolution/2,subroot->swChild);
       }
   else {
          if ( y< resolution/2)
                   return findNode(x-resolution/2,y,resolution/2,subroot->neChild);
          else 
              return findNode(x-resolution/2,y-resolution/2,resolution/2,subroot->seChild);
      }
   }
}


/* help function for rotation
 */
void Quadtree::helpRotate(QuadtreeNode* subroot){
      if(subroot == NULL)
           return;
      QuadtreeNode* temp = subroot->nwChild;
      subroot->nwChild = subroot->swChild;
      subroot->swChild = subroot->seChild;
      subroot->seChild = subroot->neChild;
      subroot->neChild = temp;
      
      helpRotate(subroot->nwChild);
      helpRotate(subroot->swChild);
      helpRotate(subroot->seChild);
      helpRotate(subroot->neChild);
}
      

void Quadtree::helpPrune(QuadtreeNode* subroot, int tolerance){
      if(subroot->nwChild == NULL)
            return;
      if(checkPrune(subroot,subroot,tolerance)){

        clearRoot(subroot->nwChild);
    
        clearRoot(subroot->neChild);
          
        clearRoot(subroot->swChild);
       
        clearRoot(subroot->seChild);
      
            return;
         }
      
         helpPrune(subroot->nwChild,tolerance);
         helpPrune(subroot->neChild,tolerance);
         helpPrune(subroot->swChild,tolerance);
         helpPrune(subroot->seChild,tolerance);
       
}


bool Quadtree::checkPrune(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance) const {
     if(subroot->nwChild == NULL)
           return checkNode(subroot,croot,tolerance); 
     
     return (checkPrune(subroot->nwChild,croot,tolerance)&&checkPrune(subroot->swChild,croot,tolerance)&&checkPrune(subroot->neChild,croot,tolerance)&&checkPrune(subroot->seChild,croot,tolerance));
             
}


bool Quadtree::checkNode(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance) const{
 
      int diffR = subroot->element.red - croot->element.red;
      int diffG = subroot->element.green - croot->element.green;
      int diffB = subroot->element.blue - croot->element.blue;
      return (diffR*diffR+diffG*diffG+diffB*diffB <= tolerance);
               
}


int Quadtree::countNum(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance) const{
     if(checkPrune(subroot,croot,tolerance))
             return 1; 
     return countNum(subroot->nwChild,subroot->nwChild,tolerance)+countNum(subroot->swChild,subroot->swChild,tolerance)+countNum(subroot->seChild,subroot->seChild,tolerance)+countNum(subroot->neChild,subroot->neChild,tolerance);
}


int Quadtree::leastT(int min,int max,int numLeaves)const{
     int mid = (min+max)/2;
     if(min == max) return min;
     if( pruneSize(mid) <=numLeaves) 
            return leastT(min,mid,numLeaves);
     else 
            return leastT(mid+1,max,numLeaves);
   
}
 








