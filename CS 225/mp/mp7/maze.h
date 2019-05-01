/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <iostream>

#include "png.h"
#include "rgbapixel.h"
#include "dsets.h"
using namespace std;

class SquareMaze{
public:
SquareMaze();
void makeMaze(int width,int height);
bool canTravel(int x, int y, int dir) const;
void setWall(int x,int y,int dir,bool exists);
vector<int> solveMaze();
PNG* drawMaze() const;
PNG* drawMazeWithSolution();

private:
int height;
int width;
vector<bool> rightW;
vector<bool> downW;
DisjointSets allSet;
void help1(int x,int y,int count,vector<int> &counter);
bool createR(int x,int y,int d,vector<int> &route);
bool isF(DisjointSets a,int limit);

};
#endif
