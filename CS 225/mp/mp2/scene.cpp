#include <iostream>
#include "scene.h"
#include "image.h"
#include "png.h"
#include <stddef.h>

using namespace std;

Scene::Scene(int max){
array =new Image*[max];
xcoords=new int[max];
ycoords=new int[max];
this->max=max;
for(int i = 0;i<max;i++){
array[i]=NULL;
xcoords[i]=0;
ycoords[i]=0;}
}

Scene::~Scene(){
 clean();
}

void Scene::clean(){
for(int i=0;i<max;i++)
delete array[i];
delete[] array;
delete xcoords;
delete ycoords;
array = NULL;
xcoords= NULL;
ycoords= NULL;
}

Scene::Scene(const Scene & source){
copy(source);
}

void Scene::copy(const Scene &other){
max=other.max;
xcoords=new int[other.max];
ycoords=new int[other.max];
array=new Image*[other.max];
for(int i=0;i<max;i++)
{  if(other.array[i]!=NULL){
    array[i]= new Image(*(other.array[i]));
    xcoords[i]=other.xcoords[i];
    ycoords[i]=other.ycoords[i];
    }
   else 
    { array[i]=NULL;
      xcoords[i]=0;
      ycoords[i]=0;
    }
}

}

const Scene & Scene::operator= (const Scene &source){
 clean();
 copy(source);
 return *this;
}

void Scene::changemaxlayers(int newmax){
if(newmax<0)
{return;}
Image** newarray=new Image*[newmax];
int *newxcoords=new int[newmax];
int *newycoords=new int[newmax];
 for(int i=0;i<newmax;i++){
   newarray[i]=NULL;
   newxcoords[i]=0;
   newycoords[i]=0;
 }

for(int i=0;i<max;i++){
  if(array[i]!=NULL && i<newmax)
    { 
      newarray[i]=array[i];
     
      newxcoords[i]=xcoords[i];
      
       newycoords[i]=ycoords[i];
      }
  else if(array[i]!=NULL && i>=newmax)
     { 
       delete[] newarray;
       delete newxcoords;
       delete newycoords;
       cout<< "invalid newmax" << endl;
       return;
        }
   }
  
delete []array;
delete []xcoords;
delete []ycoords;
array=newarray;
xcoords=newxcoords;
ycoords=newycoords;
max=newmax;


}

void Scene::addpicture(const char * FileName,int index,int x,int y){
if(index>max-1 || index<0)
{cout<<"index out of bounds" << endl;
 return;
}
else{
Image* a = new Image;
a -> readFromFile(FileName);
if(array[index]!=NULL)
{ delete array[index];}
array[index]=a;
xcoords[index]=x;
ycoords[index]=y;
}
}


void Scene::changelayer(int index,int newindex){
if(index>max-1||index<0||newindex<0 || newindex > max-1){
cout<<"invalid index" << endl;
return;}
else if(newindex==index)
return;
else {
 if(array[newindex]!=NULL)
  {
   delete array[newindex];
   array[newindex]=NULL;
  }

  array[newindex]=array[index];
  xcoords[newindex] = xcoords[index];
  ycoords[newindex] = ycoords[index]; 
  if(array[index]!=NULL)
  array[index]=NULL;
  xcoords[index]=0;
  ycoords[index]=0;
 
}
}


void Scene::translate(int index,int xcoord,int ycoord){
if((index<max&&index>=0) && array[index]!=NULL )
   { xcoords[index]=xcoord;
     ycoords[index]=ycoord;
    }
else
    cout<< "invalid index" << endl;	
}

void Scene::deletepicture(int index){
if(index>max-1||index<0 || array[index]==NULL)
{  cout << "invalid index" << endl; }
else
{  delete array[index];
   array[index]=NULL; 
   xcoords[index]=0;
   ycoords[index]=0;
}
}	

Image * Scene::getpicture(int index)const{
if(index>max-1||index<0){
cout << "invalid index" << endl;
return NULL;
}
else{
return array[index];
}
}

Image Scene::drawscene()const{
Image a=Image();
int height=0;
int width=0;
for(int i=0;i<max;i++){
  if(array[i]!=NULL)
    {  if( xcoords[i]+ (int)array[i]->width() >=width) 
       width= xcoords[i]+(int)array[i]->width();
       height=((int)(ycoords[i]+array[i]->height()) >= height) ? ycoords[i]+array[i]->height():height;
     }
}
a.resize(width,height);

for ( int i=0;i<max;i++){
    if (array[i]!=NULL){
  for (int w=xcoords[i];w<(xcoords[i]+(int)array[i]->width());w++){
   for ( int h=ycoords[i];h<(ycoords[i]+(int)array[i]->height());h++){
        *((&a)->operator()(w,h)) = *(array[i]->operator()(w-xcoords[i],h-ycoords[i]));
     }
   }
  }
 }
return a;
}







			


