#include "maze.h"

SquareMaze::SquareMaze(){
}

void SquareMaze::makeMaze (int width, int height) {
 this->width = width;	
 this->height = height;
 int size = width * height;
 for(int i = 0; i < size; i++){
   rightW.push_back(true);
   downW.push_back(true);    
 }
  allSet.addelements(size);
   int count = 0;
   srand(time(NULL));
  while(count<size/2){
  
   int numX = rand()%(width-1);
   int numY = rand()%(height-1);
   int temp = rand()%2;
   if(temp == 1) { 
   if(rightW[numY*width+numX] == true && allSet.find(numY*width+numX) != allSet.find(numY*width+numX+1))
      {
	  rightW[numY*width+numX] = false;
          allSet.setunion (numY*width+numX, numY*width+numX+1);
          count++;
          temp = 0;
        }
     }
   else {
     if(downW[numY*width+numX] == true && allSet.find(numY*width+numX) != allSet.find((numY+1)*width + numX)){
         downW[numY*width+numX] = false;
         allSet.setunion ((numY+1)*width+numX, numY*width+numX);
         count++;
         temp = 1;
        }
    }
  }
   if(isF(allSet,size))
     return;
   for(int newR = 0; newR < height-1; newR++){
     for (int newC = 0; newC < width-1; newC++){
        if(rightW[newR*width+newC] == true && allSet.find(newR*width+newC)!=allSet.find(newR*width+newC+1)){
          rightW[newR*width+newC] = false;
          allSet.setunion(newR*width+newC,newR*width+newC+1);
          }
        if(downW[newR*width+newC] == true && allSet.find(newR*width+newC)!=allSet.find((newR+1)*width+newC)){
          downW[newR*width+newC] = false;
          allSet.setunion(newR*width+newC,(newR+1)*width+newC);
          }
        }
      }
    if(isF(allSet,size))
      return;
    for(int k = 0;k<width-1;k++){
       if(rightW[(height-1)*width+k] == true && allSet.find((height-1)*width+k)!=allSet.find((height-1)*width+k+1)){
         rightW[(height-1)*width+k ] = false;
         allSet.setunion((height-1)*width+k,(height-1)*width+k+1);
        }
    } 
    if(isF(allSet,size))
      return;
    for(int j = 0; j<height-1;j++){
       if(downW[j*width+width] == true && allSet.find(j*width+width)!=allSet.find((j+1)*width+width)){
         rightW[j*width+width ] = false;
         allSet.setunion(j*width+width,(j+1)*width+width);
        }
    }
}

bool SquareMaze::canTravel(int x,int y,int dir)	const {
  if(dir == 0 && x+1!=width)
      return (rightW[y*width+x]==false);
  if(dir == 1 && y+1!=height)
      return (downW[y*width+x]==false);
  if(dir == 2 && x!=0)
      return (rightW[y*width+x-1]==false);
  if(dir == 3 && y!=0)
      return (downW[(y-1)*width+x]==false);
 
  return false;
}

void SquareMaze::setWall(int x,int y,int dir,bool exists) {
     if(dir == 0 && x+1!=width)
         rightW[y*width+x] = exists;
     if(dir == 1 && y+1!=height)
         downW[y*width+x] = exists;
}

vector<int> SquareMaze::solveMaze(){
  vector <int> route;
  vector <int> counter;
  for(int k = 0; k < width; k++) 
      counter.push_back(-1);
  help1(0,0,0,counter);
  int bestIdx = 0;
  for(size_t i = 1; i<counter.size(); i++){
      if(counter[bestIdx]<counter[i]) 
           bestIdx = i;
  }
  route.clear();
  createR(0,0,bestIdx,route);  
  return route;    
}

PNG * SquareMaze::drawMaze()const {
 PNG* result = new PNG(width*10+1,height*10+1);
 for(int i = 0;i<height*10;i++){
  (*result)(0,i)->red = 0;
  (*result)(0,i)->green = 0;
  (*result)(0,i)->blue = 0;
  }
 for(int k = 10;k<width*10;k++) {
  (*result)(k,0)->red = 0;
  (*result)(k,0)->green = 0;
  (*result)(k,0)->blue = 0;   
  }
  
  for(int y = 0;y<height;y++){
    for(int x = 0;x<width;x++){
      if(rightW[y*width+x]){
       for(int k = 0;k<=10;k++){
         (*result)((x+1)*10,y*10+k)->red = 0;    
         (*result)((x+1)*10,y*10+k)->green = 0;
         (*result)((x+1)*10,y*10+k)->blue = 0;
         }
      }
      if(downW[y*width+x]){
       for(int k = 0;k<=10;k++){
         (*result)(x*10+k,(y+1)*10)->red = 0;
         (*result)(x*10+k,(y+1)*10)->green = 0;
         (*result)(x*10+k,(y+1)*10)->blue = 0;
         }
      }
    }
  }  
  return result; 
}

PNG * SquareMaze::drawMazeWithSolution() {
   PNG* result = drawMaze();
   vector<int> route = solveMaze();
   int x = 5;
   int y = 5;
   for(size_t i =0; i<route.size();i++){
      if(route[i]==0){
       for(int k = 0; k<=10; k++){
         (*result)(x+k,y)->red = 255;
         (*result)(x+k,y)->green = 0;
         (*result)(x+k,y)->blue = 0;
        }
        x = x + 10;
      }
      else if(route[i]==1){
        for(int k = 0; k<=10; k++){
         (*result)(x,y+k)->red = 255;
         (*result)(x,y+k)->green = 0;
         (*result)(x,y+k)->blue = 0;
        }
         y = y + 10;
      }
      else if(route[i]==2){
       for(int k = 0; k<=10; k++){
         (*result)(x-k,y)->red = 255;
         (*result)(x-k,y)->green = 0;
         (*result)(x-k,y)->blue = 0;
        }
        x = x - 10;
      }
       else if(route[i]==3){
       for(int k = 0; k<=10; k++){
         (*result)(x,y-k)->red = 255;
         (*result)(x,y-k)->green = 0;
         (*result)(x,y-k)->blue = 0;
        }
        y = y - 10;
      }
   }   
   int oriX  =  x/10;
   int oriY = height-1;
   for(int k=1;k<=9;k++){
     (*result)(oriX*10+k,(oriY+1)*10)->red = 255;
     (*result)(oriX*10+k,(oriY+1)*10)->green = 255;
     (*result)(oriX*10+k,(oriY+1)*10)->blue = 255;
    }
   return result;        
}

void SquareMaze::help1(int x,int y,int count,vector<int> &counter){
   if(y == height-1)
     counter[x] = count;
   if(canTravel(x,y,0)){
     count++;
     setWall(x,y,0,true);
     help1(x+1,y,count,counter);
     count --;
     setWall(x,y,0,false);
    }
   if(canTravel(x,y,1)){
     count++;
     setWall(x,y,1,true);
     help1(x,y+1,count,counter);
     count --;
     setWall(x,y,1,false);
    }
   if(canTravel(x,y,2)){
     count++;
     setWall(x-1,y,0,true);
     help1(x-1,y,count,counter);
     count --;
     setWall(x-1,y,0,false);
    }
   if(canTravel(x,y,3)){
     count++;
     setWall(x,y-1,1,true);
     help1(x,y-1,count,counter);
     count --;
     setWall(x,y-1,1,false);
    }

  return;     
}

bool SquareMaze::createR(int x,int y,int d,vector<int> &route){
      if(y == height-1 && x==d) 
          return true;
      if(canTravel(x,y,0)){
        route.push_back(0);
        setWall(x,y,0,true);
        if(createR(x+1,y,d,route)){ 
           setWall(x,y,0,false);
           return true;
          }
        setWall(x,y,0,false);
        route.pop_back();  
      }
 
    if(canTravel(x,y,1)){
        route.push_back(1);
        setWall(x,y,1,true);
        if(createR(x,y+1,d,route)){
           setWall(x,y,1,false);
           return true;
          }
        setWall(x,y,1,false);
        route.pop_back();
      }
 
    if(canTravel(x,y,2)){
        route.push_back(2);
        setWall(x-1,y,0,true);
        if(createR(x-1,y,d,route)){
           setWall(x-1,y,0,false);
           return true;
          }
        setWall(x-1,y,0,false);
        route.pop_back();
      }
  
     if(canTravel(x,y,3)){
        route.push_back(3);
        setWall(x,y-1,1,true);
        if(createR(x,y-1,d,route)){
           setWall(x,y-1,1,false);
           return true;
          }
        setWall(x,y-1,1,false);
        route.pop_back();
      }
     
      return false;
}

bool SquareMaze::isF(DisjointSets a,int limit){
     for(int i=0;i<limit-1;i++)
     { 
       if(a.find(i)!=a.find(i+1))
        return false;
      }
     return true;
} 	
