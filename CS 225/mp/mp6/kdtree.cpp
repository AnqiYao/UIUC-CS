/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cstddef>
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if(first[curDim] < second[curDim])
             return true;
	if (first[curDim]>second[curDim]){
		return false;
	}
	else {
		return (first<second);
	}
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{   int difference1 = 0;
    int difference2 = 0;
    for( int i = 0; i< Dim; i++) {
       difference1 += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
       difference2 += (target[i]-potential[i])*(target[i]-potential[i]);
      }
    if(difference1 < difference2) 
            return false;
    else if( difference1 > difference2) 
            return true;
    else  
       return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{ 
    if (newPoints.empty())
        points = newPoints; 
   else { 
     points = newPoints; 
     helpBuild(points,0,points.size()-1,0);
     }
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
 /*   int least = 0; 
    for(size_t i =1; i < points.size();i++) {
          if(shouldReplace(query,points[least],points[i]))
              least = i;
      }
   
    return points[least];
 */
  Point<Dim> curBest;
  bool checkLr = false ;
  helpFind(query,curBest,0,points.size()-1,0,checkLr);  
  return curBest;
}

// help function is below 

template <int Dim>
void KDTree<Dim>::helpBuild(vector<Point<Dim>> & subpoint,int min, int max, int d) const{
       if ( min >= max )  return;
       selectionSort(subpoint,min,max,d);
       d = (d +1)%Dim;
       int mid = (min+max)/2;
      // if(mid == min||mid==max) 
       //    return;
       helpBuild (subpoint,min,mid-1,d);
       helpBuild (subpoint,mid+1,max,d);
        

}

template <int Dim>
void KDTree<Dim>::selectionSort(vector<Point<Dim>> & subpoint, int min, int max,int d)  const {
       if (min == max) return; 
       int least = min;
       Point<Dim> temp = subpoint[min];  
       while( min!= max) {
         for( int i = min; i<=max; i++) {
              if (subpoint[i][d]<subpoint[least][d]) {
                  least = i; 
                  temp = subpoint[i];
                }	
		if (subpoint[i][d]==subpoint[least][d]){
			if (subpoint[i]<subpoint[least]){
			least=i;
			temp=subpoint[i];
		}
		}
           }
        subpoint[least] = subpoint[min];
        subpoint[min] = temp;
        min ++; 
        temp = subpoint[min];
        least =  min ;
      }                                
}

template <int Dim>
void KDTree<Dim>::helpFind(const Point<Dim>& subpoint,Point<Dim>& curBest,int min, int max,int d,bool checkLr) const{
      if( min >= max) 
       {    
            if (checkLr){
             
            if(shouldReplace(subpoint,curBest,points[min]))  
             curBest = points[min];
                } 
           else {
            
             if(shouldReplace(subpoint,curBest,points[max]))   
             curBest = points[max];
             }
            return;
         }
      int mid = (min+max)/2;
      if (smallerDimVal(subpoint,points[mid],d)){
           helpFind(subpoint,curBest,min,mid-1,(d+1)%Dim,true);
           if (shouldReplace(subpoint,curBest,points[mid]))
                     curBest = points[mid]; 
           int radius =0;
           for( int i = 0; i< Dim; i++) {
            radius += (subpoint[i]-curBest[i])*(subpoint[i]-curBest[i]);}
           if( (subpoint[d] - points[mid][d])*(subpoint[d] - points[mid][d]) <= radius)
                helpFind(subpoint,curBest,mid+1,max,(d+1)%Dim,false); 
         }
      else {
           helpFind(subpoint,curBest,mid+1,max,(d+1)%Dim,false);
           if (shouldReplace(subpoint,curBest,points[mid])) 
                     curBest = points[mid];
           int radius =0;
           for( int i = 0; i< Dim; i++) {
           radius += (subpoint[i]-curBest[i])*(subpoint[i]-curBest[i]);}
           if( (subpoint[d] - points[mid][d])*(subpoint[d] - points[mid][d]) <= radius)
                helpFind(subpoint,curBest,min,mid-1,(d+1)%Dim,true); 
         }
              
}



