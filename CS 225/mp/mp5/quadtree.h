/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
     Quadtree();
     Quadtree(PNG const& source, int resolution);
     Quadtree(Quadtree const& other);     
     ~Quadtree();
     Quadtree const& operator=(Quadtree const& other);
     void buildTree(PNG const& source,int resolution);
     RGBAPixel getPixel(int x,int y) const;
     PNG decompress() const; 
    
   // mp5.2 
  
     void clockwiseRotate();
     void prune(int tolerance);
     int pruneSize(int tolerance) const;
     int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int sideLen;
    QuadtreeNode* copy(const QuadtreeNode* subroot);
    void clear();
    void clearRoot(QuadtreeNode* &subroot);   
    QuadtreeNode* helpBuild(PNG const& source,int startX, int startY, int resolution);
    QuadtreeNode* findNode(int x, int y,int resolution,QuadtreeNode* subroot) const;
    void helpRotate(QuadtreeNode* subroot); 
    void helpPrune(QuadtreeNode* subroot, int tolerance); 
    bool checkPrune(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance)const;   
    bool checkNode(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance)const;
    int countNum(QuadtreeNode* subroot, QuadtreeNode* croot, int tolerance) const;
    int leastT(int min,int max,int numLeaves)const;
/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif